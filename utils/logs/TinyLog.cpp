//
// Created by FancyKing on 2021/5/1.
//

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "TinyLog.h"
#include "iostream"


TinyLog::TinyLog(std::string log_name): _log_name(log_name) {
    _logger = spdlog::stdout_color_mt(_log_name);
    spdlog::set_level(spdlog::level::debug);
    _logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n] [%l] %v");
    _logger->warn("{0} logger has been init, use STDOUT", _log_name);
}

TinyLog::TinyLog(int max_size, int max_files, std::string file_path, std::string log_name)
        : _max_size(max_size), _max_files(max_files), _file_path(std::move(file_path)), _log_name(std::move(log_name)) {
    _logger = spdlog::rotating_logger_mt(
           _log_name,
           "logs/" + _file_path,
            max_size,
            max_files);
    spdlog::set_level(spdlog::level::debug);
    _logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    _logger->warn("{0} logger has been init, file saved in logs/{1}", "TinyStatus", _file_path);
}

void TinyLog::debug(const std::string &msg) {
    _logger->debug(msg);
}

void TinyLog::info(const std::string &msg) {
    _logger->info(msg);
}

void TinyLog::warn(const std::string &msg) {
    _logger->warn(msg);
}

void TinyLog::error(const std::string &msg) {
    _logger->error(msg);
}
