#include "sensor.hpp"
#include "logger.hpp"
#include "utils.hpp"

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
    dataBuffer.pop();
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

std::chrono::seconds Sensor::getFileTimeout() {
    return std::chrono::seconds(this->fileTimeout);
}

void Sensor::enableRegexFilter(std::string regex) {
    this->enableRegexFilterFlag = true;
    this->regexFilter = regex;
}
