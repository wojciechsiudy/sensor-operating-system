#ifndef MANAGER_HPP
#define MANAGER_HPP


#include <vector>
#include "sensor.hpp"


class Manager {
    private:
        std::vector<Sensor> sensors;

    public:
        Manager();

        void addSensor(Sensor sensor);
};

#endif