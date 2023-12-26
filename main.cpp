#include <iostream>
#include <csignal>
#include <atomic>
#include "manager.hpp"
#include "utils.hpp"
#include "serialSensor.hpp"
#include "cliParser.hpp"

namespace
{
    volatile std::atomic<bool> shutdownRequsted = 0;
}

void signal_handler(int signal)
{
    shutdownRequsted = 1;
}



int main(int argc, char *argv[]) {
    std::signal(SIGINT, signal_handler);

    auto arguments = parseArguments(argc, argv);
    if (!arguments.correct) return 1;

    if (arguments.clearOutput) {
        std::cout << "Clearing previous outputs..." << std::endl;
        clearOutput();
    }

    std::cout << "Loading configuration..." << std::endl;
    if (arguments.hasConfigPath) {
        Configuration::getConfiguration()->load(arguments.configPath);
    }
    else {
        Configuration::getConfiguration()->load("sos_config.json");
    }
    Configuration::getConfiguration()->print();

    Manager manager = Manager();

    if(arguments.hasOutputPath) {
        manager.createSerializers(arguments.outputPath);
    }
    else {
        manager.createSerializers();
    }

    manager.runSensors();
    std::cout << "Sensors running!" << std::endl;
    while(shutdownRequsted == 0 || !manager.isReady()) {};
    manager.stopSensors();
    std::cout << "Exiting..." << std::endl;
    return 0;
}
