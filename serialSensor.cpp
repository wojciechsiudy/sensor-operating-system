#include "serialSensor.hpp"

SerialSensor::SerialSensor(std::string name, std::string port, int baudrate, int timeout) : Sensor(name) {
    this->port = port;
    this->baudrate = baudrate;
    this->timeout = timeout;
}

