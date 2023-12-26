#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include <iostream>
#include <string>

struct CliArguments {
    bool correct = true;
    bool clearOutput = false;
    bool hasOutputPath = false;
    std::string outputPath;
    bool hasConfigPath = false;
    std::string configPath;
};

void printHelp() {
    std::cout << "Sensor operating system.\n" <<
            "An application that serializes data from multiple devices.\n\n" <<
            "OPTIONS:\n" <<
            "\t-c\t\t\tclear previous output\n" <<
            "\t-i <filename>\tpath to configuration file\n" <<
            "\t-o <catalog name>\tpath to output file\n\n" <<
            "CREDITS:\n" <<
            "(c) Wojciech Siudy 2023\n";
}

CliArguments parseArguments(int argc, char *argv[]) {
    CliArguments arguments;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            arguments.correct = false;
        }
        else if(strcmp(argv[i],"-c") == 0) {
            arguments.clearOutput = true;
        }
        else if(strcmp(argv[i],"-o") == 0) {
            arguments.hasOutputPath = true;
            i++;
            arguments.outputPath = argv[i];
        }
        else if(strcmp(argv[i],"-i") == 0) {
            arguments.hasConfigPath = true;
            i++;
            arguments.configPath = argv[i];
        }
        else {
            if (arguments.correct) {
                arguments.correct = false;
                printHelp();
            }
        }
    }
    return arguments;
}



#endif