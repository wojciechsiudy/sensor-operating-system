#include <chrono>

class Data {
    private:
        std::chrono::time_point<std::chrono::system_clock> timestamp;
    public:
        Data();
        Data(std::chrono::time_point<std::chrono::system_clock> timestamp);
};