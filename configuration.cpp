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

        if(json_data.contains("mqqt_server")) {

        }
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

    std::unique_ptr<Sensor> sensor;

    auto type = json["type"];
    if (type == "external") {
        sensor = std::make_unique<ExternalSensor>(
            json["name"],
            json["command"]
        );
    }
    else if (type == "serial") {
        sensor = std::make_unique<SerialSensor>(
            json["name"],
            json["path"],
            json["baudrate"],
            json["timeout"]
        );
    }
    else if (type == "network"){
        throw std::runtime_error("Network sensor in not implemented!");
    }
    else {
        throw std::runtime_error("Invalid sensor type in config file");
    }

    if(json.contains("mqqt_settings")) {
        sensor.get()->enableMqqt(parseMqqtSettings(json["mqqt_settings"]));
    }

    if(json.contains("file_timeout")) {
        sensor.get()->enableFileTimeout(json["file_timeout"]);
    }

    return sensor;
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

mqqtSettings Configuration::parseMqqtSettings(json input) {
    mqqtDataMode dataMode;
    if (input["mode"] == "selective") {
        dataMode = mqqtDataMode::selective;
    }
    else if (input["mode"] == "average") {
        dataMode = mqqtDataMode::average;
    }
    else {
        throw std::runtime_error("Invalid mqqt data mode in config file");
    }

    return {
        input["topic"],
        input["delay"],
        dataMode
    };
}