//
// Created by FancyKing on 2021/5/16.
//

#include "config.h"

const std::string &Config::getName() const {
    return _name;
}

void Config::setName(const std::string &name) {
    _name = name;
}

const std::string &Config::getDescription() const {
    return _description;
}

void Config::setDescription(const std::string &description) {
    _description = description;
}

const std::string &Config::getRemoteIp() const {
    return _remote_ip;
}

void Config::setRemoteIp(const std::string &remoteIp) {
    _remote_ip = remoteIp;
}

const std::string &Config::getRemotePort() const {
    return _remote_port;
}

void Config::setRemotePort(const std::string &remotePort) {
    _remote_port = remotePort;
}

const std::string &Config::getPassword() const {
    return _password;
}

void Config::setPassword(const std::string &password) {
    _password = password;
}

const int &Config::getInterval() const {
    return _interval;
}

void Config::setInterval(const int &interval) {
    _interval = interval;
}

const std::string &Config::getLogMode() const {
    return _log_mode;
}

void Config::setLogMode(const std::string &logMode) {
    _log_mode = logMode;
}

const std::pair<std::string, std::string> &Config::getSubIf() const {
    return _sub_if;
}

void Config::setSubIf(const std::pair<std::string, std::string> &subIf) {
    _sub_if = subIf;
}

const std::vector<std::pair<std::string, std::string>> &Config::getNetInterface() const {
    return _net_interface;
}

void Config::setNetInterface(const std::vector<std::pair<std::string, std::string>> &netInterface) {
    _net_interface = netInterface;
}
