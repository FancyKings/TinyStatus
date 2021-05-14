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

    if (argc < 2) {
        logger->error("Please set the profile path.");
    }

    auto conf_parser = std::make_shared<Parser>(argv[1]);
    auto config_set = conf_parser->get_config();

    auto cpu = std::make_shared<CPU>();
    auto memory = std::make_shared<Memory>();
    auto network = std::make_shared<Network>();

    for (auto &item : config_set->getNetInterface()) {
        network->add_if_name(item.first);
    }

    for (int i = 0; i < 1; ++i) {
        std::cout << cpu->get_usage().dump(4) << std::endl;
        std::cout << memory->get_usage().dump(4) << std::endl;
        std::cout << network->get_usage().dump(4) << std::endl;
        sleep(2);
    }

    return 0;
}
