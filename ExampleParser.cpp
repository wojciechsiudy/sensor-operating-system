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
            putParsedData("0.54335,-1.43141,3.31512");
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
