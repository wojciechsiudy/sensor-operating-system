#include "manager.hpp"
#include "serialSensor.hpp"


Manager::Manager() {
    this->configuration.load("../sos_config.json");
    this->configuration.print();
    this->sensors = this->configuration.createSensors();
}


void Manager::createSensor(std::string inputData) {
    //assuming intput data as a type (at the beginning)
    if (inputData == "serial") {
        this->sensors.emplace_back(std::make_unique<SerialSensor>("licznik", "/dev/ttyUSB0", 115200, 1000));
    }
    else if (inputData == "cpp") {

    }

}

void Manager::runSensors() {
    std::cout << "Sensors amount: " << this->sensors.size() << std::endl;
    for (auto& sensor : this->sensors) {
        this->sensor_threads.emplace_back(&Sensor::testRun, sensor.get());
    }
}

std::string Manager::getLastValuesOfAllSensors(){
    std::string lastValues;
    for (auto& sensor : this->sensors) {
        lastValues.append(sensor.get()->getLatestData().lock()->toString());
        lastValues.append(",");
    }
    return lastValues;
}

void Manager::stopSensors() {
    for (auto& sensor : this->sensors) {
        sensor.get()->stop();
    }
}
