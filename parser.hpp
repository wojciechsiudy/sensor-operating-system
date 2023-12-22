#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;
constexpr auto NOTIFY_DELAY = 500ms;

class Parser {
protected:
    std::vector<unsigned char> byteBuffer;
    std::mutex bytesMutex;
    std::condition_variable bytesContitionVariable;

    std::vector<std::string> parsedDataBuffer;
    std::mutex parsedDataMutex;
    std::condition_variable parsedDataConditionVariable;

    std::atomic<bool> runToken = true;

    // access methods for parser

    unsigned char swallowByte();
    void putParsedData(std::string data);

public:
    virtual ~Parser() {}

    // pointers for plugin load and unload functions

    typedef Parser* create_t();
    typedef void destroy_t(Parser*);

    // access methods for sensor

	void putByte(unsigned char byte);
    std::string reciveLastProcessedData();

    // start and stop methods

    virtual void parse() = 0;
    void stopParser() { runToken = false; parsedDataConditionVariable.notify_all(); }

    bool getRunToken() {return runToken;}
};

#endif
