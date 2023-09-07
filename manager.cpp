#include "manager.hpp"

Manager::Manager() {
    
}

void Manager::addSensor(Sensor sensor) {
    this->sensors.push_back(sensor);
}
