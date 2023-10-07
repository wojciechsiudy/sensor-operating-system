#ifndef DATA_HPP
#define DATA_HPP

#include <chrono>
#include <string>

class Data {
    private:
        std::chrono::time_point<std::chrono::system_clock> timestamp;
    public:
        Data();
        virtual std::string toString();
        virtual ~Data() noexcept = default;
};

#endif