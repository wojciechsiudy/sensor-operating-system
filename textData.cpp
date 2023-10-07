#include "textData.hpp"

TextData::TextData(std::string data) : Data() {
    this->line = data;
}

std::string TextData::toString() {
    auto baseString = Data::toString();
    return baseString + this->line;
}