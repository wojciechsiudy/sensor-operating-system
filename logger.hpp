#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <thread>
#include <string>
#include <mutex>
#include "sensor.hpp"

enum class LogLevel {
    quitet,
    normal,
    verbose
};


class Logger {
    static Logger* instance;
    static std::mutex mutex;
    LogLevel logLevel;
protected:
    Logger() {};
    ~Logger() {};
public:
    void operator=(const Logger&) = delete;

    static Logger *getLogger();

    void write(std::string message);
};

#endif
