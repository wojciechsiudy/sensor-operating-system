#include <filesystem>
#include "serializer.hpp"
#include "configuration.hpp"
#include "utils.hpp"

Serializer::Serializer( std::shared_ptr<Sensor>& sensor,
                        std::string directoryName) {
    this->sensorReference = sensor;
    this->outputDirectoryName = directoryName;

    if (sensorReference.expired()) {
        throw std::runtime_error("Sensor expired!");
    }

    std::string currentRunDirectoryName = outputDirectoryName + "/" +
        Configuration::getConfiguration()->getStartTimeString();

    this->baseFilePath.append(currentRunDirectoryName + "/");

    std::filesystem::create_directories(this->baseFilePath);

    this->serializationThread = std::jthread(&Serializer::manageWriting, this);
}

std::string Serializer::makeFileName() {
    std::string result = this->baseFilePath;
    result.append(this->sensorReference.lock().get()->getName());
    result.append("-");
    result.append(std::to_string(this->fileCounter));
    return result;
}

void Serializer::manageWriting() {
    auto fileTimeout = this->sensorReference.lock().get()->getFileTimeout();
    auto timeElapsed = std::chrono::seconds(0);
    auto timeStart = std::chrono::steady_clock::now();

    this->file.open(makeFileName());

    while (true and this->stopFlag == false) {
        try {
            this->file <<
                this->sensorReference.lock().get()->getAndPopNextData()->toString()
                << std::endl;

            timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - timeStart);
            if (timeElapsed > fileTimeout) {
                this->file.close();
                this->fileCounter++;
                this->file.open(makeFileName());
                timeStart = std::chrono::steady_clock::now();
            }
        }
        catch (EmptyBuffer) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(milisecondsAtferBufferUnderflow));
        }
    }

    this->file.close();
}

Serializer::~Serializer() {
    this->stopFlag = true;
}



