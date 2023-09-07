#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>

class Sensor {
    private:
        std::string name;
    public:
        Sensor();
        Sensor(std::string name);
};

#endif