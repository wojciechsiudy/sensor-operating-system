#include "manager.hpp"
#include "serialSensor.hpp"

Manager::Manager() {
    
}

void Manager::createSensor(std::string inputData) {
    //assuming intput data as a type (at the beginning)
    if (inputData == "serial") {
        this->sensors.emplace_back(std::make_shared<SerialSensor>("licznik", "/dev/ttyUSB0", 115200, 1000));
    }
    else if (inputData == "cpp") {

    }

}

void Manager::testManager() {
    createSensor("serial");

    for (auto sensor : this->sensors) {
        sensor->testRun();
    }
    
}

