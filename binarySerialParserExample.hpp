#ifndef BINARY_SERIAL_PARSER_EXAMPLE_HPP
#define BINARY_SERIAL_PARSER_EXAMPLE_HPP

#include "parserInterface.hpp"

extern "C" class ExampleParser : public ParserInterface{
    public:
    virtual void parse() override;
};

#endif