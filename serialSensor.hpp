#ifndef SERIALSENSOR_HPP
#define SERIALSENSOR_HPP

#include <string>

#include <serial/serial.h>

#include "sensor.hpp"


class SerialSensor : public Sensor
{
    private:
        std::string port;
        int baudrate;
        int timeout;

    serial::Serial serial;
    public:
        SerialSensor(std::string name, std::string port, int baudrate, int timeout);
        void open() {

        }

};

#endif