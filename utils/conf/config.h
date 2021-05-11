//
// Created by FancyKing on 2021/5/16.
//

#ifndef TINYSTATUS_CONFIG_H
#define TINYSTATUS_CONFIG_H

#include "vector"
#include "string"

class Config {
private:
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getRemoteIp() const;

    void setRemoteIp(const std::string &remoteIp);

    const std::string &getRemotePort() const;

    void setRemotePort(const std::string &remotePort);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const int &getInterval() const;

    void setInterval(const int &interval);

    const std::string &getLogMode() const;

    void setLogMode(const std::string &logMode);

    const std::pair<std::string, std::string> &getSubIf() const;

    void setSubIf(const std::pair<std::string, std::string> &subIf);

    const std::vector<std::pair<std::string, std::string>> &getNetInterface() const;

    void setNetInterface(const std::vector<std::pair<std::string, std::string>> &netInterface);

private:
    std::string _name;
    std::string _description;
    std::string _remote_ip;
    std::string _remote_port;
    std::string _password;
    int _interval;
    std::string _log_mode;
    std::pair<std::string, std::string> _sub_if;
    std::vector<std::pair<std::string, std::string>> _net_interface;
};


#endif //TINYSTATUS_CONFIG_H
