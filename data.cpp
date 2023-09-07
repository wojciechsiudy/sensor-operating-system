#include "data.hpp"

Data::Data() {
    this->timestamp = std::chrono::system_clock::now();
}

Data::Data(std::chrono::time_point<std::chrono::system_clock> timestamp) {
    this->timestamp = timestamp;
}