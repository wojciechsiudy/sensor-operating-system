#include <fstream>
#include <iostream>
#include <filesystem>

#include "configuration.hpp"

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
    std::cout << "Sensors: " << this->sensors << std::endl;
}
