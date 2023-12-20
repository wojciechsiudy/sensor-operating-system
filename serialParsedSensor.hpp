#ifndef SERIAL_PARSED_SENSOR_HPP
#define SERIAL_PARSED_SENSOR_HPP

#include <string>
#include "serialSensor.hpp"
#include "parser.hpp"
#include "pluginHandler.hpp"

class SerialParsedSensor : public SerialSensor {
    std::shared_ptr<Parser> parser;

public:
    SerialParsedSensor( std::string name, std::string serialPath,
                        int baudrate, int timeout,
                        std::string parserPath);

    virtual void run() override;
};


#endif
