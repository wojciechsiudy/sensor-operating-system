#include "serialParsedSensor.hpp"
#include "utils.hpp"

SerialParsedSensor::SerialParsedSensor(
                                        std::string name,
                                        std::string serialPath,
                                        int baudrate, int timeout,
                                        std::string parserPath) :
                        SerialSensor(   name, serialPath,
                                        baudrate, timeout) {
    auto parserHandler = new PluginHandler<Parser>(parserPath);
    this->parser = parserHandler->make_obj();
    delete parserHandler;

    if (!parser) {
        throw std::runtime_error("Parser loading failed!");
    }
}

void SerialParsedSensor::run() {
    this->prepareSerialConnection();
    std::jthread parserThread([&](){parser->parse();});

    std::vector<uint8_t> intermediateBuffer;
    while (! this->getStopFlag()) {
        serial.read(intermediateBuffer); // load from serial
        parser->putByte(intermediateBuffer.back()); // transfer to plugin
        intermediateBuffer.pop_back();
        if (getStopFlag()) parser->stopParser();
        auto data = parser->reciveLastProcessedData();
        // try {
        //     pushData(std::make_shared<SerialData>(
        //         parser->reciveLastProcessedData()
        //     ));
        // }
        // catch (EmptyBuffer) {}
        intermediateBuffer.clear();
    }
    std::cout << "SerialParsedSensor stop req";
    parser->stopParser();
}
