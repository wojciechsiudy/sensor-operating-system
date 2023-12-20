// g++ -shared -fPIC ExampleParser.cpp -o plugin.so

#ifndef EXAMPLE_PARSER_HPP
#define EXAMPLE_PARSER_HPP

#include <iostream>
#include "parser.hpp"

class ExampleParser : public Parser {
public:
    virtual void parse() override {
        while (runToken) {
            auto tmp = swallowByte();
            putParsedData(std::to_string(tmp));
        }
    };
};


// class factory

extern "C" Parser* create() {
    return new ExampleParser();
}

extern "C" void destroy(Parser* ptr) {
    delete ptr;
}


#endif