//
// Created by FancyKing on 2021/5/3.
//

#ifndef TINYSTATUS_NET_H
#define TINYSTATUS_NET_H

#include "../../utils/logs/TinyLog.h"
#include "../../utils/json/json.hpp"
#include "../../utils/fmt/core.h"
#include "../../utils/fmt/ranges.h"
#include "vector"
#include "set"
#include "string"
#include "iostream"
#include "fstream"
#include "chrono"
#include "regex"

using json = nlohmann::json;

class Network {
public:

    Network();

    json get_usage();
    int add_if_name(const std::string &if_name);

private:
    const static std::string _rx_link;
    const static std::string _tx_link;
    const static std::string _if_link;
    std::set<std::string> _if_vec;
    std::set<std::string> _if_valid_vec;
    unsigned long long _pre_rx_bytes{};
    unsigned long long _pre_tx_bytes{};
    unsigned long long _tx_bytes{};
    unsigned long long _rx_bytes{};
    unsigned int _pre_timestamp;
    std::shared_ptr<TinyLog> _net_log;

    static long long _get_ts();
    void _get_if_vec();
    bool _invalid_if_name(const std::string& if_name);
    json _get_if_usage(const std::string &if_name);
};


#endif //TINYSTATUS_NET_H
