#ifndef EXTERNALSENSOR_HPP
#define EXTERNALSENSOR_HPP

#ifdef _WIN32
#error Nie będzie i koniec
#endif


#include "sensor.hpp"

#include <cstdio>
#include <iostream>

#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "textData.hpp"

// std::string exec(const char* cmd) {
//     std::array<char, 128> buffer;
//     std::string result;
//     std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//     if (!pipe) {
//         throw std::runtime_error("popen() failed!");
//     }
//     while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//         result += buffer.data();
//     }
//     return result;
// }

class ExternalSensor : public Sensor {
   private:
    std::shared_ptr<FILE> pipe;
    std::string command;
   public:
    ExternalSensor(std::string name, std::string command) : Sensor(name), command(command) {}

    void run(){
        std::cout << "External sensor test run" << std::endl;
        while(true){
            if (this->getStopFlag()) {
                break;
            }
            this->pushData(std::make_shared<TextData>("bleble"));
        }
    }

    virtual void testRun() override;
};

#endif