//
// Created by FancyKing on 2021/5/3.
//

#include "net.h"

const std::string Network::_rx_link = "/sys/class/net/{}/statistics/rx_bytes";
const std::string Network::_tx_link = "/sys/class/net/{}/statistics/tx_bytes";
const std::string Network::_if_link = "/proc/net/dev";

Network::Network() {
    _net_log = std::make_shared<TinyLog>("network");
    _get_if_vec();
    // just for develop without config file.
    _if_vec.insert("eth0");
    _pre_timestamp = _get_ts();
}

json Network::get_usage() {
    json usage;
    for (auto &if_name : _if_vec) {
        json sub_if = _get_if_usage(if_name);
        usage[if_name] = sub_if;
    }
    return usage;
}

json Network::_get_if_usage(const std::string &if_name) {
    if (_invalid_if_name(if_name)) {
        _net_log->warn(fmt::format("The interface name {} not available.", if_name));
    }

    json sub_if;
    std::string target_link = fmt::format(_rx_link, if_name);
    std::ifstream if_read(target_link);
    if_read >> _rx_bytes;

    target_link = fmt::format(_tx_link, if_name);
    if_read.open(target_link);
    if_read >> _tx_bytes;

    auto now_ts = _get_ts();
    if (now_ts == _pre_timestamp) {
        now_ts += 1;
    }

    sub_if["rx"] = fmt::format("{:.3f}",
                               static_cast<double>((_rx_bytes - _pre_rx_bytes) / (now_ts - _pre_timestamp)) * 0.008);
    sub_if["tx"] = fmt::format("{:.3f}",
                               static_cast<double>((_tx_bytes - _pre_tx_bytes) / (now_ts - _pre_timestamp)) * 0.008);

    _pre_rx_bytes = _rx_bytes;
    _pre_tx_bytes = _tx_bytes;
    _pre_timestamp = now_ts;

    return sub_if;
}

long long Network::_get_ts() {
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
}

void Network::_get_if_vec() {
    std::ifstream dev_read(_if_link);
    std::regex self_regex("(\\w+):", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::smatch result;

    std::string line;
    while (dev_read) {
        dev_read >> line;
        if (std::regex_search(line, result, self_regex)) {
            _if_valid_vec.insert(result.str());
        }
    }
}

bool Network::_invalid_if_name(const std::string &if_name) {
    return static_cast<bool>(_if_valid_vec.count(if_name));
}

int Network::add_if_name(const std::string &if_name) {
    if (_invalid_if_name(if_name)) {
        return 0;
    }
    _if_vec.insert(if_name);
    return 1;
}
