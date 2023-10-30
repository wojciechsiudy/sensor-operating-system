#include <iostream>
#include <thread>
#include <chrono>
#include "externalSensor.hpp"
#include "textData.hpp"

ExternalSensor::ExternalSensor(std::string name, std::string command)
        : Sensor(name), command(command) {
            messageQueueAttributes.mq_flags = 0;
            messageQueueAttributes.mq_maxmsg = 10;
            messageQueueAttributes.mq_msgsize = MAX_SIZE;
            messageQueueAttributes.mq_curmsgs = 0;

            messageQueue = mq_open(
                /*@todo: Fix name parser*/
                "/pytest_queue",
                O_CREAT | O_RDONLY,
                0664,
                &messageQueueAttributes
            );
            CHECK((mqd_t)-1 != messageQueue);
}

const char* ExternalSensor::createQueueName() {
    std::string qName = "/";
    qName.append(this->getName());
    qName.append("_queue");
    return qName.c_str();
}

void ExternalSensor::run() {

    std::jthread commandThread([this](){system(this->command.c_str());});
    //FILE* subprocess = popen(this->command.c_str(), "r");

    while(! this->getStopFlag()) {
        ssize_t bytesRead;

        bytesRead = mq_receive(
            messageQueue,
            this->buffer,
            MAX_SIZE,
            NULL);

        this->buffer[bytesRead] = '\0';
        this->pushData(std::make_shared<TextData>(buffer));

    }
    std::cout << "requesting ext command stop" << std::endl;

    commandThread.detach(); //will be killed once the whole applcation stops

    mq_close(this->messageQueue);
    mq_unlink(createQueueName());
}