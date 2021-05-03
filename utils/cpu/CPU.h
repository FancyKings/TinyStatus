//
// Created by FancyKing on 2021/5/2.
//

#ifndef TINYSTATUS_CPU_H
#define TINYSTATUS_CPU_H

#include "../../utils/json/json.hpp"
#include "../../utils/logs/TinyLog.h"
#include "vector"
#include "fstream"
#include "iostream"
#include "numeric"
#include "unistd.h"

using json = nlohmann::json;

class CPU {
public:

    CPU();

    json get_usage();

private:
    int _idle_time{};
    int _total_time{};
    int _pre_idle_time{};
    int _pre_total_time{};
    static int _cpu_id;

    static std::vector<int> _get_cpu_times();

    std::shared_ptr<TinyLog> _cpu_log{};
};


#endif //TINYSTATUS_CPU_H
