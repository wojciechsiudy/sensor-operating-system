#ifndef MANAGER_HPP
#define MANAGER_HPP


#include <list>
#include <memory>
#include "sensor.hpp"
#include "configuration.hpp"

class Manager {
    private:
        std::list<std::unique_ptr<Sensor>> sensors;
        Configuration configuration;
    public:
        Manager();

        

        /**
         * Creates sensor based on input data
        */
        void createSensor(std::string inputData);

        /**
         * Quasi-test function
        */
        void testManager();

};

#endif