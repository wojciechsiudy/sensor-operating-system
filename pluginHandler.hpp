// References:
//  [https://www.linuxjournal.com/article/3687],
//  [https://github.com/arturb-dev/CPP-Dynamic-Class-Loading]

#ifndef PLUGIN_HANDLER_HPP
#define PLUGIN_HANDLER_HPP

#include <memory>
#include <string>
#include <dlfcn.h>
#include <iostream>

template <class T>
class PluginHandler {
    struct shared_obj {
        typename T::create_t *create = nullptr;
        typename T::destroy_t *destroy = nullptr;
        void * pluginHandle = nullptr;

        ~shared_obj();
        bool open_module(std::string module);
        void close_module();
    };

    std::string module;
    std::shared_ptr<shared_obj> shared;

public:
    PluginHandler(std::string module_name);
    ~PluginHandler();

    template <typename... Args>
    std::shared_ptr<T> make_obj(Args... args);
};


template <class T>
PluginHandler<T>::PluginHandler(std::string module_name) :
    module(module_name){
    shared = std::make_shared<shared_obj>();
}

template <class T>
PluginHandler<T>::~PluginHandler() {
    //close_module();
}

template <class T>
void PluginHandler<T>::shared_obj::close_module() {
    if(pluginHandle) {
        dlclose(pluginHandle);
        pluginHandle = nullptr;
    }
    if(create) create = nullptr;
    if(destroy) destroy = nullptr;
}

template <class T>
bool PluginHandler<T>::shared_obj::open_module(std::string module) {

    pluginHandle = dlopen(module.c_str(), RTLD_LAZY);

    if(!pluginHandle) {
        std::cerr << "Failed to open library: " << dlerror() << std::endl;
        return false;
    }

    // Reset errors
    dlerror();

    create = (typename T::create_t*) dlsym(pluginHandle, "create");
    const char * err = dlerror();
    if(err) {
        std::cerr << "Failed to load create symbol: " << err << std::endl;
        close_module();
        return false;
    }

    destroy = (typename T::destroy_t*) dlsym(pluginHandle, "destroy");
    err = dlerror();
    if(err) {
        std::cerr << "Failed to load destroy symbol: " << err << std::endl;
        close_module();
        return false;
    }

    return true;
}

template <class T> template< typename... Args>
std::shared_ptr<T> PluginHandler<T>::make_obj(Args... args) {
    if(!shared->create || !shared->destroy) {
        if(!shared->open_module(module)) {
            return std::shared_ptr<T>(nullptr);
        }
    }

//    auto create_args = ((T* (*)(Args...))create);
    std::shared_ptr<shared_obj> my_shared = shared;
    return std::shared_ptr<T>(shared->create(args...),
                              [my_shared](T* p){ my_shared->destroy(p); });
}


template <class T>
PluginHandler<T>::shared_obj::~shared_obj() {
    close_module();
}

#endif
