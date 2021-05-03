//
// Created by FancyKing on 2021/5/2.
//

#include "memory.h"


Memory::Memory() {
    _mem_log = std::make_shared<TinyLog>("memory");
}

json Memory::get_usage() {
    json usage;
    int error = sysinfo(&_sys_info);
    if (error != 0) {
        _mem_log->error(fmt::format("Failed to obtain system information"
                                    ", The error code is {}.", error)
        );
    }

    _virtual_total_mem = _sys_info.totalram;
    _virtual_total_mem += _sys_info.totalswap;
    _virtual_total_mem *= _sys_info.mem_unit;

    _virtual_used_mem = _sys_info.totalram - _sys_info.freeram;
    _virtual_used_mem += _sys_info.totalswap - _sys_info.freeswap;
    _virtual_used_mem *= _sys_info.mem_unit;

    _physical_total_mem = _sys_info.totalram * _sys_info.mem_unit;

    _physical_used_mem = _sys_info.totalram - _sys_info.freeram;
    _physical_used_mem *= _sys_info.mem_unit;

    _swap_total_mem = _sys_info.totalswap;

    _swap_used_mem = _sys_info.totalswap - _sys_info.freeswap;

    usage["virtual_total"] = _virtual_total_mem / 1024 / 1024;
    usage["virtual_used"] = _virtual_used_mem / 1024 / 1024;
    usage["physical_total"] = _physical_total_mem / 1024 / 1024;
    usage["physical_used"] = _physical_used_mem / 1024 / 1024;
    usage["swap_total"] = _swap_total_mem / 1024 / 1024;
    usage["swap_used"] = _swap_used_mem / 1024 / 1024;

    return usage;
}
