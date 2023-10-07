#include "sensor.hpp"

Sensor::Sensor(std::string name)
{
    this->name = name;
}

std::shared_ptr<Data> Sensor::getLastData()
{
    std::unique_lock<std::mutex> lock(this->dataMutex);
    if (this->dataBuffer.empty())
    {
        throw EmptyBuffer();
    }
    auto tmp = this->dataBuffer.front();
    this->dataBuffer.pop();
    return tmp;
}

#include <iostream>

void Sensor::pushData(std::shared_ptr<Data> data)
{
    std::lock_guard<std::mutex> lock(this->dataMutex);
    this->dataBuffer.push(std::move(data));
}