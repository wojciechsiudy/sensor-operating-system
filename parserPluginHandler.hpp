#ifndef PARSER_PLUGIN_PARSER_HPP
#define PARSER_PLUGIN_PARSER_HPP

#include "serialSensor.hpp"
#include "streamProcessorResources.hpp"

typedef void (*parserFunctionHandle)();

class ParserPluginHandler {
    void *parserLibrary;
    parserFunctionHandle parser;

public:
    ParserPluginHandler(std::string pathToLibrary);

    ~ParserPluginHandler();

};

#endif