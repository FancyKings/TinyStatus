//
// Created by FancyKing on 2021/5/17.
//

#ifndef TINYSTATUS_CONNECT_H
#define TINYSTATUS_CONNECT_H

#include "string"
#include "unistd.h"
#include "cstdio"
#include "sys/socket.h"
#include "cstdlib"
#include "netinet/in.h"
#include "cstring"
#include "utility"
#include "arpa/inet.h"
#include "../../utils/logs/TinyLog.h"
#include "../../utils/json/json.hpp"

using json = nlohmann::json;

class Connect {
public:
    explicit Connect(std::string remote_addr = "172.22.192.1",
                     std::string remote_port = "8080");

    bool set_addr_port(const std::string &remote_addr,
                       const std::string &remote_port);

    std::string send_msg(const std::string &message);

    std::string recv_msg() const;

    std::string build_json_post(const json &message);

private:
    std::shared_ptr<TinyLog> _connect_log{};
    std::string _remote_addr;
    std::string _remote_port;
    struct sockaddr_in _remote_sockaddr;
    int _sock_id;

    bool _set_addr_port();

    bool _connect();
};


#endif //TINYSTATUS_CONNECT_H
