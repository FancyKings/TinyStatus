//
// Created by FancyKing on 2021/5/2.
//

#ifndef TINYSTATUS_MEMORY_H
#define TINYSTATUS_MEMORY_H

#include "sys/types.h"
#include "sys/sysinfo.h"
#include "../../utils/json/json.hpp"
#include "../../utils/logs/TinyLog.h"
#include "../../utils/fmt/core.h"

using json = nlohmann::json;

class Memory {
public:

    Memory();

    json get_usage();

private:
    unsigned long _virtual_total_mem{};
    unsigned long _virtual_used_mem{};
    unsigned long _physical_total_mem{};
    unsigned long _physical_used_mem{};
    unsigned long _swap_total_mem{};
    unsigned long _swap_used_mem{};
    struct sysinfo _sys_info{};
    std::shared_ptr<TinyLog> _mem_log{};
};


#endif //TINYSTATUS_MEMORY_H
