//
// Created by FancyKing on 2021/5/1.
//

#ifndef TINYSTATUS_TINYLOG_H
#define TINYSTATUS_TINYLOG_H

#include <spdlog/spdlog.h>
#include <iostream>
#include "spdlog/sinks/rotating_file_sink.h"
#include "string"

class TinyLog {

public:
    TinyLog(int max_size = 1024 * 1024 * 5,
            int max_files = 3,
            std::string file_path = "rot_log.log",
            std::string log_name = "TinyStatus");

    TinyLog(std::string log_name = "TinyStatus");

    void debug(const std::string &msg);

    void info(const std::string &msg);

    void warn(const std::string &msg);

    void error(const std::string &msg);

private:
    int _max_size{};
    int _max_files{};
    std::string _file_path;
    std::string _log_name;
    std::shared_ptr<spdlog::logger> _logger;
};


#endif //TINYSTATUS_TINYLOG_H
