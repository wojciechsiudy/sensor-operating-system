#ifndef SERIAL_SENSOR_HPP
#define SERIAL_SENSOR_HPP

#include <string>
#include <serial/serial.h>
#include "sensor.hpp"

constexpr int BYTES_BUFFER_SIZE = 4096;

class SerialSensor : public Sensor {
    void reciveLine();
    void reciveAndProcessStream();

protected:
    serial::Serial serial;
    void prepareSerialConnection();

public:
    SerialSensor(std::string name, std::string port, int baudrate, uint32_t timeout = 1000);
    virtual void run() override;
};


class SerialData : public Data {
    std::string line;

public:
    SerialData(std::string data);

    std::string toString() override;
};

#endif