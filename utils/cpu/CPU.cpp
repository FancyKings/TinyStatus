//
// Created by FancyKing on 2021/5/2.
//

#include "CPU.h"

int CPU::_cpu_id = 0;

CPU::CPU()
        : _total_time(0), _pre_total_time(0), _idle_time(0), _pre_idle_time(0) {
    _cpu_log = std::make_shared<TinyLog>("cpu_" + std::to_string(_cpu_id++));
    get_usage();
}

json CPU::get_usage() {
    json usage;
    auto cpu_times = _get_cpu_times();
    if (cpu_times.size() < 4) {
        _cpu_log->error("CPU idle time is not obtained.");
        return json();
    }
    _idle_time = cpu_times[3];
    _total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);

    double idle_delta = _idle_time - _pre_idle_time;
    double total_delta = _total_time - _pre_total_time;
    usage["idle"] = fmt::format("{:.3f}", 100.0 * (idle_delta / total_delta));
    usage["active"] = fmt::format("{:.3f}", 100.0 * (1.0 - idle_delta / total_delta));
    _pre_idle_time = _idle_time;
    _pre_total_time = _total_time;
    return usage;
}

std::vector<int> CPU::_get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    // skip "cpu  "
    proc_stat.ignore(5, ' ');
    std::vector<int> times;
    for (int time; proc_stat >> time; times.emplace_back(time));
    times.shrink_to_fit();
    proc_stat.close();
    return times;
}