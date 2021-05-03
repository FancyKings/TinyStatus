#include "iostream"
#include "utils/logs/TinyLog.h"
#include "utils/cpu/CPU.h"
#include "utils/memory/memory.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    auto logger = new TinyLog("MAIN");
    logger->warn("TEST");

    auto cpu = std::make_shared<CPU>();
    auto memory = std::make_shared<Memory>();
    for (int i = 0; i < 20; ++i) {
        std::cout << cpu->get_usage().dump(4) << std::endl;
        std::cout << memory->get_usage().dump(4) << std::endl;
        sleep(1);
    }

    return 0;
}
