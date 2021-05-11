#include "iostream"
#include "utils/logs/TinyLog.h"
#include "utils/cpu/CPU.h"
#include "utils/memory/memory.h"
#include "utils/net/net.h"
#include "utils/conf/parser.h"
#include "utils/conf/config.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char const * argv[]) {
    auto logger = new TinyLog("MAIN");
    logger->warn("TEST");

    auto cpu = std::make_shared<CPU>();
    auto memory = std::make_shared<Memory>();
    auto network = std::make_shared<Network>();
    for (int i = 0; i < 1; ++i) {
        std::cout << cpu->get_usage().dump(4) << std::endl;
        std::cout << memory->get_usage().dump(4) << std::endl;
        std::cout << network->get_usage().dump(4) << std::endl;
        sleep(2);
    }

    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            std::cout << argv[i] << std::endl;
        }
        auto conf_parser = std::make_shared<Parser>(argv[1]);
    }

    return 0;
}
