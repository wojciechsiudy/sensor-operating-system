#include <iostream>
#include "manager.hpp"

#include "serialSensor.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Start" << std::endl;
    Manager manager = Manager();
    manager.runSensors();
    std::cout << "Sensors running" << std::endl;
    for(int i = 0; i < 5; i++){
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << manager.getLastValuesOfAllSensors() << std::endl;
    }
    manager.stopSensors();
    return 0;
}
