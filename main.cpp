#include <iostream>
#include <csignal>
#include <atomic>
#include "manager.hpp"
#include "utils.hpp"
#include "serialSensor.hpp"

namespace
{
    volatile std::atomic<bool> shutdownRequsted = 0;
}

void signal_handler(int signal)
{
    shutdownRequsted = 1;
}

int main(int argc, char* argv[]) {
    std::signal(SIGINT, signal_handler);
    clearOutput();

    std::cout << "Loading configuration..." << std::endl;
    Manager manager = Manager();
    manager.runSensors();
    std::cout << "Sensors running" << std::endl;
    while(shutdownRequsted == 0 || !manager.isReady()) {};

    manager.stopSensors();
    std::cout << "Exiting..." << std::endl;
    return 0;
}
