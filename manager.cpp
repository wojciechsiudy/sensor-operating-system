#include <iostream>
#include "manager.hpp"
#include "serialSensor.hpp"

Manager::Manager() {
    this->sensors = Configuration::getConfiguration()->createSensors();
}

void Manager::runSensors() {
    std::cout << "Sensors amount: " << this->sensors.size() << std::endl;
    for (auto& sensor : this->sensors) {
        this->sensor_threads.emplace_back(&Sensor::run, sensor.get());
    }
    systemReady = true;
}

std::string Manager::getLastValuesOfAllSensors(){
    std::string lastValues;
    for (auto& sensor : this->sensors) {
        if(sensor.get()->hasData()) {
            lastValues.append(sensor.get()->getLatestData().lock()->toString());
            lastValues.append(",");
        }

    }
    return lastValues;
}

void Manager::stopSensors() {
    for (auto& sensor : this->sensors) {
        sensor->stop();
    }
}

void Manager::createSerializers(std::string outputPath) {
    for (auto& sensor : sensors) {
        serializers.emplace_back(std::make_shared<Serializer>(sensor, outputPath));
    }
}