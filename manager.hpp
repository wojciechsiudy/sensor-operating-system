#ifndef MANAGER_HPP
#define MANAGER_HPP


#include <list>
#include <memory>
#include "sensor.hpp"


class Manager {
    private:
        std::list<std::shared_ptr<Sensor>> sensors;

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