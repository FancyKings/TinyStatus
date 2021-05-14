//
// Created by FancyKing on 2021/5/3.
//

#include "parser.h"

Parser::Parser(std::string conf_path)
        : _conf_path(conf_path) {
    std::ifstream conf_stream(_conf_path);
    conf_stream >> _conf_json;
    _config = std::make_shared<Config>();
    read_users_config();
//    std::cout << _conf_json["description"].get<std::string>() << std::endl;
}

void Parser::read_users_config() {
    _config->setName(_conf_json["name"].get<std::string>());
    _config->setDescription(_conf_json["description"].get<std::string>());
    _config->setRemoteIp(_conf_json["remote_addr"].get<std::string>());
    _config->setRemotePort(_conf_json["remote_port"].get<std::string>());
    _config->setPassword(_conf_json["password"].get<std::string>());
    _config->setInterval(std::stoi(_conf_json["interval"].get<std::string>()));
    std::vector<std::pair<std::string, std::string>> net_if;
    for (auto &item : _conf_json["interface"]) {
        net_if.emplace_back(std::make_pair(item["name"], item["description"]));
    }
    _config->setNetInterface(net_if);
}

const std::shared_ptr<Config> &Parser::get_config() const {
    return _config;
}
