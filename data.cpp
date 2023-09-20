#include "data.hpp"

Data::Data() {
    this->timestamp = std::chrono::system_clock::now();
}

std::string Data::toString() {
    return (std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(this->timestamp.time_since_epoch()).count()) + "|");
}