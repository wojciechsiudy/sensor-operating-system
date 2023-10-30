#include "sensor.hpp"

Sensor::Sensor(std::string name)
{
    this->name = name;
}

std::shared_ptr<Data> Sensor::getAndPopNextData()
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

std::weak_ptr<Data> Sensor::getLatestData()
{
    std::unique_lock<std::mutex> lock(this->dataMutex);
    if (this->dataBuffer.empty())
    {
        throw EmptyBuffer();
    }
    return this->dataBuffer.back();
}

void Sensor::pushData(std::shared_ptr<Data> data)
{
    std::lock_guard<std::mutex> lock(this->dataMutex);
    this->dataBuffer.push(std::move(data));
}

void Sensor::enableMqqt(mqqtSettings settings) {
    this->enableMqqtFlag = true;
    this->mqqt = settings;
}

void Sensor::enableFileTimeout(int timeout) {
    this->enableFileTimeoutFlag = true;
    this->fileTimeout = timeout;
}