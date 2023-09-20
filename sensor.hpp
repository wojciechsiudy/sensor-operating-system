#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <queue>
#include <thread>
#include <memory>
#include "data.hpp"

class Sensor {
    private:
        std::string name;
        std::queue<std::shared_ptr<Data>> dataBuffer;


    public:

        Sensor() = default;

        Sensor(std::string name);

        //virtual void initialize() = 0;

        virtual void testRun() = 0;
        
        void pushData(std::shared_ptr<Data> data);

        std::shared_ptr<Data> getLastData();

        ~Sensor() noexcept = default;

};

struct EmptyBuffer : public std::exception {
   const char * what () const throw () {
      return "Buffer is empty";
   }
};

#endif