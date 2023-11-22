#include <filesystem>
#include "serializer.hpp"

Serializer::Serializer(std::shared_ptr<Sensor>& sensor) {
    this->sensorReference = sensor;

    if (sensorReference.expired()) {
        throw std::runtime_error("Sensor expired!");
    }

    if (!std::filesystem::exists(outputDirectoryName)) {
        std::filesystem::create_directory(outputDirectoryName);
    }

    this->baseFilePath =
        this->sensorReference.lock().get()->getName();

    this->serializationThread = std::jthread(&Serializer::manageWriting, this);
}

std::string Serializer::makeFileName() {
    std::string result = this->baseFilePath;
    result.append("-");
    result.append(std::to_string(this->fileCounter));
    return result;
}

void Serializer::manageWriting() {
    auto fileTimeout = this->sensorReference.lock().get()->getFileTimeout();
    auto timeElapsed = std::chrono::duration<int>(0);
    auto timeStart = std::chrono::steady_clock::now();

    this->file.open(makeFileName());

    while (true and this->stopFlag == false) {
        try {
            this->file <<
                this->sensorReference.lock().get()->getAndPopNextData()->toString()
                << std::endl;
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



