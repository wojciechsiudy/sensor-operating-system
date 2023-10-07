#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <queue>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "data.hpp"

class Sensor {
    private:
        std::string name;
        std::queue<std::shared_ptr<Data>> dataBuffer;
        std::condition_variable dataCondition;
        std::mutex dataMutex;
        bool stopFlag = false;
    public:

        Sensor() = default;

        Sensor(std::string name);

        //virtual void initialize() = 0;

        virtual void testRun() = 0;
        
        void pushData(std::shared_ptr<Data> data);

        std::shared_ptr<Data> getLastData();

        virtual ~Sensor() = default;

        inline void stop() {this->stopFlag = true;}

        inline bool getStopFlag() {return this->stopFlag;}

};

struct EmptyBuffer : public std::exception {
   const char * what () const throw () {
      return "Buffer is empty";
   }
};

#endif