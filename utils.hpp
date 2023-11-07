#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <string>
#include <iomanip>


std::string makeHumanReadableTime(std::chrono::time_point<std::chrono::system_clock> time) {
    std::time_t time_c = std::chrono::system_clock::to_time_t(time);
    return std::ctime(&time_c);

}

std::string makeFilenameWritableTime(std::chrono::time_point<std::chrono::system_clock> time) {
    std::time_t time_c = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&time_c);
    std::stringstream buffer;
    buffer << std::put_time(&tm, "%Y-%m--%d-%H:%M:%S");
    return buffer.str();
}


#endif