#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <queue>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "data.hpp"

enum class mqqtDataMode {
    average,
    selective
};

struct mqqtSettings {
    std::string topic;
    int delay;
    mqqtDataMode mode;
};

class Sensor {
    private:
        std::string name;

        std::queue<std::shared_ptr<Data>> dataBuffer;
        std::mutex dataMutex;

        std::atomic<bool> stopFlag = false;

        bool enableMqqtFlag = false;
        mqqtSettings mqqt;

        bool enableFileTimeoutFlag = false;
        int fileTimeout = 300; /*seconds*/

        bool enableRegexFilterFlag = false;
        std::string regexFilter;

        bool enableParserFlag = false;
        std::string parserPath;

        u_int max_buffer_size = 1024;
    public:

        Sensor() = default;

        Sensor(std::string name);

        virtual void run() = 0;

        void pushData(std::shared_ptr<Data> data);

        std::shared_ptr<Data> getAndPopNextData();

        std::weak_ptr<Data> getLatestData();

        virtual ~Sensor() = default;

        inline void stop() {this->stopFlag = true;}

        inline bool getStopFlag() {return this->stopFlag;}

        inline bool hasData() {return !this->dataBuffer.empty();}

        inline std::string getName() {return this->name;}

        inline bool isMqqtEnabled() {return this->enableMqqtFlag;}

        void enableMqqt(mqqtSettings settings);

        void enableFileTimeout(int timeout);

        std::chrono::seconds getFileTimeout();

        void enableRegexFilter(std::string regex);

        inline bool isRegexFilterEnabled() {return this->enableRegexFilterFlag;}

        inline std::string getRegexFilter() {return this->regexFilter;}

        inline std::string getParserPath() {return this->parserPath;}
};

#endif