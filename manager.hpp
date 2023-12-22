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
        std::atomic<bool> systemReady = false;
    public:
        Manager();

        void runSensors();

        std::string getLastValuesOfAllSensors();

        void stopSensors();

        bool isReady() {return systemReady;}

    private:
        void createSerializers();
};

#endif