#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <string>
#include <iomanip>
#include <filesystem>

std::string makeHumanReadableTime(std::chrono::time_point<std::chrono::system_clock> time);

std::string makeFilenameWritableTime(std::chrono::time_point<std::chrono::system_clock> time);

void clearOutput();


#endif