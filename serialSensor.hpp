#ifndef SERIALSENSOR_HPP
#define SERIALSENSOR_HPP

#include <string>
#include <serial/serial.h>
#include "sensor.hpp"


class SerialSensor : public Sensor
{
    private:
        serial::Serial serial;
        void reciveLine();

    public:
        SerialSensor(std::string name, std::string port, int baudrate, uint32_t timeout = 1000);
        virtual void testRun() override;

};




class SerialData : public Data
{
    private:
        std::string line;
    public:
        SerialData(std::string data);

        std::string toString() override;
        
};

#endif