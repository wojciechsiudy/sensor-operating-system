#ifndef MANAGER_HPP
#define MANAGER_HPP


#include <list>
#include <memory>
#include <thread>
#include "configuration.hpp"
#include "serialSensor.hpp"
#include "externalSensor.hpp"

class Manager {
    private:
        std::list<std::unique_ptr<Sensor>> sensors;
        std::list<std::jthread> sensor_threads;
        Configuration configuration;
    public:
        Manager();

        void runSensors();

        std::string getLastValuesOfAllSensors();

        void stopSensors();
};

#endif