#include <iostream>
#include "manager.hpp"
#include "utils.hpp"
#include "serialSensor.hpp"

int main(int argc, char* argv[]) {
    //clearOutput();
    std::cout << "Start" << std::endl;
    Manager manager = Manager();
    manager.runSensors();
    std::cout << "Sensors running" << std::endl;
    for(int i = 0; i < 10; i++){
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
    manager.stopSensors();
    return 0;
}
