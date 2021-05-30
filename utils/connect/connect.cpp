//
// Created by FancyKing on 2021/5/17.
//

#include "connect.h"


Connect::Connect(std::string remote_addr, std::string remote_port)
        : _remote_addr(std::move(remote_addr)), _remote_port(std::move(remote_port)) {
    _connect_log = std::make_shared<TinyLog>("Connect");
    _set_addr_port();
}

bool Connect::set_addr_port(const std::string &remote_addr, const std::string &remote_port) {
    _remote_addr = remote_addr;
    _remote_port = remote_port;
    return _set_addr_port();
}

bool Connect::_set_addr_port() {
    _sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock_id < 0) {
        _connect_log->error("Create socket failed");
        return false;
    }
    _remote_sockaddr.sin_family = AF_INET;
    _remote_sockaddr.sin_port = htons(
            static_cast<unsigned short>(std::stoi(_remote_port)));
    auto addr_valid = inet_pton(AF_INET, _remote_addr.c_str(), &_remote_sockaddr.sin_addr);
    if (addr_valid <= 0) {
        _connect_log->error("Invalid remote address");
        return false;
    }
    return true;
}

bool Connect::_connect() {
    // connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0
    auto success = connect(_sock_id, (struct sockaddr *) &_remote_sockaddr, sizeof(_remote_sockaddr));
    if (success < 0) {
        _connect_log->error("Failed to connect");
        return false;
    }
    return true;
};

std::string Connect::send_msg(const std::string &message) {
    if (!_connect()) {
        return std::string();
    }
    send(_sock_id, message.c_str(), message.size(), 0);
    _connect_log->debug(fmt::format("Sent message {}", message.c_str()));
    return recv_msg();
}

std::string Connect::build_json_post(const json &message) {
    return fmt::format(
            "POST /api/cpptest HTTP/1.1\r\n"
            "Host: {}\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: {}\r\n"
            "Connection: close\r\n\r\n"
            "{}", _remote_addr, message.dump().size(), message.dump()
    );
}

std::string Connect::recv_msg() const {
    char *buffer_recv = new char[1024];
    std::string recv_msg;
    auto recv_size = 0;
    while ((recv_size = recv(_sock_id, buffer_recv, sizeof(buffer_recv) - 1, 0)) > 0) {
        buffer_recv[recv_size] = '\0';
        recv_msg += std::string(buffer_recv);
    }
    return recv_msg.append("\r\n");
}
