#include <iostream>
#include "manager.hpp"
#include "utils.hpp"
#include "serialSensor.hpp"

int main(int argc, char* argv[]) {
    //clearOutput();
    std::cout << "Loading configuration..." << std::endl;
    Manager manager = Manager();
    manager.runSensors();
    std::cout << "Sensors running" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    manager.stopSensors();
    return 0;
}
