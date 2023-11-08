#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <queue>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>
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

        bool stopFlag = false;

        bool enableMqqtFlag = false;
        mqqtSettings mqqt;

        bool enableFileTimeoutFlag = false;
        int fileTimeout = 300; /*seconds*/

        bool enableRegexFilterFlag = false;
        std::string regexFilter;
    public:

        Sensor() = default;

        Sensor(std::string name);

        //virtual void initialize() = 0;

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

        std::chrono::duration<int> getFileTimeout();

        void enableRegexFilter(std::string regex);

        inline bool isRegexFilterEnabled() {return this->enableRegexFilterFlag;}

        inline std::string getRegexFilter() {return this->regexFilter;}
};

struct EmptyBuffer : public std::exception {
   const char * what () const throw () {
      return "Buffer is empty";
   }
};

#endif