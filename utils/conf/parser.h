//
// Created by FancyKing on 2021/5/3.
//

#ifndef TINYSTATUS_PARSER_H
#define TINYSTATUS_PARSER_H

#include "../../utils/json/json.hpp"
#include "../../utils/logs/TinyLog.h"
#include "../../utils/fmt/core.h"
#include "../../utils/conf/config.h"
#include "string"
#include "iostream"
#include "fstream"

using json = nlohmann::json;

class Parser {
public:
    explicit Parser(std::string conf_path);
    const std::shared_ptr<Config> &get_config() const;

private:
    std::string _conf_path;
    json _conf_json;
    std::shared_ptr<Config> _config;

    void read_users_config();
};

#endif //TINYSTATUS_PARSER_H
