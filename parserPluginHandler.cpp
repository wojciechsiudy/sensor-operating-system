#include <dlfcn.h>
#include <string>
#include <iostream>
#include <vector>
#include "parserPluginHandler.hpp"

ParserPluginHandler::ParserPluginHandler(std::string pathToLibrary) {
    
    parserLibrary = dlopen(pathToLibrary.c_str(), RTLD_NOW);
    if (!parserLibrary) {
        throw std::runtime_error(("dlopen() error: %s\n", dlerror()));
    }

    parser = reinterpret_cast<parserFunctionHandle>(dlsym(parserLibrary, "parser"));
    if (!parser) {
        throw std::runtime_error(("dlsym() error: %s\n", dlerror()));
    }


}

ParserPluginHandler::~ParserPluginHandler() {
    try {
        dlclose(parserLibrary);
    }
    catch (std::exception& e) {
        std::cout << "Error while closing library: " << e.what() << std::endl;
    }
}