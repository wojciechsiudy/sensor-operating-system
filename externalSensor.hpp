#ifndef EXTERNALSENSOR_HPP
#define EXTERNALSENSOR_HPP

#include <mqueue.h>
#include "sensor.hpp"

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

constexpr auto MAX_SIZE = 1024;
constexpr auto MSG_STOP = "exit";

class ExternalSensor : public Sensor {
    std::string command;
    mqd_t messageQueue;
    struct mq_attr messageQueueAttributes;
    char buffer[MAX_SIZE + 1];

public:
    ExternalSensor(std::string name, std::string command);

    void run();

    virtual void testRun() override;

private:
    const char* createQueueName();
};

#endif