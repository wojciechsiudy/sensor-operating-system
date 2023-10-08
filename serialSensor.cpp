#include <iostream>
#include "serialSensor.hpp"

SerialSensor::SerialSensor(std::string name, std::string port, int baudrate, uint32_t timeout) : Sensor(name) {
    this->serial.setPort(port);
    this->serial.setBaudrate(baudrate);
    this->serial.setTimeout(serial::Timeout::max(), timeout, 0, timeout, 0);
}

void SerialSensor::reciveLine() {
        auto line = this->serial.readline();
        this->pushData(std::make_shared<SerialData>(line));
}

void SerialSensor::testRun() {
    if (!this->serial.isOpen()) {
        this->serial.open();
    }
    while (true) {
        if (this->getStopFlag()) {
            break;
        }
        reciveLine();
        try {
            std::cout << this->getAndPopNextData().get()->toString() << std::endl;
        }
        catch (EmptyBuffer &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

SerialData::SerialData(std::string data) : Data() {
    this->line = data;
}

std::string SerialData::toString() {
    auto baseString = Data::toString();
    return baseString + this->line;
}

