#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class SensorType {
    serial,
    cpp,
    python,
    network,
    external
};

class Configuration {
    std::string name;
    std::string version;
    std::string author;
    json sensors;
public:
    void load(const std::string& filename);
    void save(const std::string& filename);
    //void set(const std::string& key, const std::string& value);
    void print();
};

#endif