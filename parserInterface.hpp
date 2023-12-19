#ifndef STREAM_PROCESSOR_RESOURCES_HPP
#define STREAM_PROCESSOR_RESOURCES_HPP

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>

class ParserInterface {
protected:
    std::vector<unsigned char> byteBuffer;
    std::mutex bytesMutex;
    std::condition_variable bytesContitionVariable;

    std::vector<std::string> parsedDataBuffer;
    std::mutex parsedDataMutex;
    std::condition_variable parsedDataConditionVariable;
public:
	void publishByte(unsigned char byte);
    virtual void parse() = 0;
	std::string reciveLastProcessedData();
};

#endif
