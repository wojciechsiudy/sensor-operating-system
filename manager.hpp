#ifndef MANAGER_HPP
#define MANAGER_HPP


#include <list>
#include <memory>
#include <thread>
#include "configuration.hpp"
#include "serialSensor.hpp"
#include "externalSensor.hpp"
#include "serializer.hpp"

class Manager {
    private:
        std::list<std::shared_ptr<Sensor>> sensors;
        std::list<std::jthread> sensor_threads;

        std::list<std::shared_ptr<Serializer>> serializers;
    public:
        Manager();

        void runSensors();

        std::string getLastValuesOfAllSensors();

        void stopSensors();

    private:
        void createSerializers();
};

#endif