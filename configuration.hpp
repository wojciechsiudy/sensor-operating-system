#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <memory>
#include <map>
#include <list>
#include <chrono>
#include <nlohmann/json.hpp>
#include "sensor.hpp"

using json = nlohmann::json;

struct mqqtServerData {
    std::string address;
    int port;
    std::string username;
    std::string password;
};

class Configuration {
    static Configuration* instance;
    static std::mutex mutex;

    std::string name;
    std::string version;
    std::string author;
    u_int max_buffer_size = 1024;
    json sensors = json::array();

    std::chrono::time_point<std::chrono::system_clock> createTime;

    bool mqqtSupport = false;
    mqqtServerData mqqt;
protected:
    Configuration() {};
    ~Configuration() {};
public:
    static Configuration *getConfiguration();
    void load(const std::string& filename);
    void save(const std::string& filename);
    void print();
    std::string getStartTimeString();
    std::list<std::shared_ptr<Sensor>> createSensors();
    u_int getMaxBufferSize() {return max_buffer_size;};
private:
    std::shared_ptr<Sensor> createSensorFromJson(json json);
    mqqtSettings parseMqqtSettings(json input);
};

#endif