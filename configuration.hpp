#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <memory>
#include <map>
#include <list>
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
    std::string name;
    std::string version;
    std::string author;
    json sensors = json::array();

    bool mqqtSupport = false;
    mqqtServerData mqqt;
public:
    void load(const std::string& filename);
    void save(const std::string& filename);
    //void set(const std::string& key, const std::string& value);
    void print();
    std::list<std::unique_ptr<Sensor>> createSensors();
private:
    std::unique_ptr<Sensor> createSensorFromJson(json json);
    mqqtSettings parseMqqtSettings(json input);
};

#endif