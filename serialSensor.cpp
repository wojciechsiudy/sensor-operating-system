#include <iostream>
#include "serialSensor.hpp"

SerialSensor::SerialSensor(std::string name, std::string port, int baudrate, uint32_t timeout) : Sensor(name) {
    this->serial.setPort(port);
    this->serial.setBaudrate(baudrate);
    this->serial.setTimeout(serial::Timeout::max(), timeout, 0, timeout, 0);
}

void SerialSensor::reciveLine() {
        auto line = this->serial.readline();
        // drop the newline
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());
        this->pushData(std::make_shared<SerialData>(line));
}

void SerialSensor::run() {
    if (!this->serial.isOpen()) {
        this->serial.open();
    }
    if (!this->serial.available()) {
        throw std::runtime_error("Serial port {} is unavaliable"); //fixme
    }
    while (! this->getStopFlag()) {
        reciveLine();
    }
}

SerialData::SerialData(std::string data) : Data() {
    this->line = data;
}

std::string SerialData::toString() {
    auto baseString = Data::toString();
    return baseString + this->line;
}

