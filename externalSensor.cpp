#include <iostream>
#include <thread>
#include <chrono>
#include <sys/prctl.h>
#include <signal.h>
#include <sstream>
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
    pid_t pid = fork();

    // the following 'if' statements are entered whenever
    // child or parent are invoking it
    if (pid == 0) {
        // Child process
        std::istringstream iss(this->command);
        std::string interpreter, script;
        iss >> interpreter >> script;
        execl(interpreter.c_str(), interpreter.c_str(), script.c_str(), (char *)NULL);
        _exit(EXIT_FAILURE);   // exec never returns if it's successful
    }
    else if (pid < 0) {
        // Fork failed
        throw std::runtime_error("fork() failed!");
    }
    else {
        // Parent process
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
        kill(pid, SIGTERM);  // send SIGTERM to the child process
    }
}