#include <fstream>
#include <iostream>
#include <filesystem>

#include "configuration.hpp"
#include "externalSensor.hpp"
#include "serialSensor.hpp"

using json = nlohmann::json;

void Configuration::load(const std::string& filename) {

    try {
        if (!std::filesystem::exists(filename)) {
            std::cout << "Config file does not exist" << std::endl;
            std::exit(1);
        }
        std::ifstream file(filename);
        auto json_data = json::parse(file);

        this->name = json_data["name"];
        this->version = json_data["version"];
        this->author = json_data["author"];
        this->sensors = json_data["sensors"];
    }
    catch (std::exception& e) {
        std::cout << "Error while loading configuration file: " << e.what() << std::endl;
        std::exit(1);
    }

    


}

void Configuration::print() {
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Version: " << this->version << std::endl;
    std::cout << "Author: " << this->author << std::endl;

}


std::unique_ptr<Sensor> Configuration::createSensorFromJson(json json) {
    if (json.is_null()) {
        std::cout << "Sensor is null" << std::endl;
        return nullptr;
    }

    auto type = json["type"];
    if (type == "external") {
        return std::make_unique<ExternalSensor>(
            json["name"],
            json["command"]
        );
    }
    else if (type == "serial") {
        return std::make_unique<SerialSensor>(
            json["name"],
            json["path"],
            json["baudrate"],
            json["timeout"]
        );
    }
    else if (type == "network"){
        //todo
    }
    else {
        throw std::runtime_error("Invalid sensor");
    }
}

std::list<std::unique_ptr<Sensor>> Configuration::createSensors() {
    std::list<std::unique_ptr<Sensor>> result;
    
    if (this->sensors.size() == 0) {
        std::cout << "No sensors defined" << std::endl;
        std::exit(1);
    }
    for (auto& sensor_json : this->sensors) {
        result.emplace_back(createSensorFromJson(sensor_json));
    }

    return std::move(result);
}