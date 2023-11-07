#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <chrono>
#include "sensor.hpp"

class Serializer {
    std::string baseFileName;
    std::chrono::time_point<std::chrono::system_clock> fileCreationTime;
    int fileCounter = 0;
public:
    Serializer(Sensor& sensor);
};

#endif