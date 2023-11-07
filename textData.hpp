#include <string>
#include "data.hpp"

class TextData : public Data
{
    private:
        std::string line;
    public:
        TextData(std::string data);

        std::string toString() override;

};