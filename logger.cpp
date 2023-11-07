#include <iostream>
#include "logger.hpp"

Logger* Logger::getLogger() {
    std::lock_guard<std::mutex> lock(mutex);
    if(instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

Logger::~Logger() {
    delete instance;
}

void Logger::write(std::string message) {
    std::cout << message << std::endl;
}