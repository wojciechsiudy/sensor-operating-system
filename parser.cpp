#include <dlfcn.h>
#include <iostream>
#include "parser.hpp"
#include "utils.hpp"

// bytes producer
void Parser::putByte(unsigned char byte) {
    std::unique_lock<std::mutex> lock(bytesMutex);
    byteBuffer.push_back(byte);
    bytesContitionVariable.notify_one();
}

//bytes consumer
unsigned char Parser::swallowByte() {
    std::unique_lock lock(bytesMutex);
    bytesContitionVariable.wait(lock, [&](){ return !(byteBuffer.empty() && runToken); });
    auto tmp = byteBuffer.back();
    byteBuffer.pop_back();
    return tmp;
}

// parsed producer
void Parser::putParsedData(std::string data) {
    std::unique_lock<std::mutex> lock(parsedDataMutex);
    parsedDataBuffer.push_back(data);
    parsedDataConditionVariable.notify_one();
}

// parsed consumer
std::string Parser::reciveLastProcessedData() {
    if (!runToken) throw EmptyBuffer();
    std::unique_lock<std::mutex> lock(parsedDataMutex);
    parsedDataConditionVariable.wait(lock, [&](){ return !(parsedDataBuffer.empty() && runToken); });
    auto tmp = parsedDataBuffer.back();
    parsedDataBuffer.pop_back();
    return tmp;
}