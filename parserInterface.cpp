#include <dlfcn.h>
#include <iostream>
#include "parserInterface.hpp"

void ParserInterface::publishByte(unsigned char byte) {
    byteBuffer.push_back(byte);
}

std::string ParserInterface::reciveLastProcessedData() {
    auto val = parsedDataBuffer.back();
    parsedDataBuffer.pop_back();
    return val;
}