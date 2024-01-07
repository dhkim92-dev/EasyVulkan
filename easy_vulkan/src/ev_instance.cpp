#ifndef __EV_INSTANCE_CPP__
#define __EV_INSTANCE_CPP__

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <unordered_set>
#include "ev_instance.h"
#include "ev_debug.h"

using namespace std;
using namespace EasyVulkan;
using namespace EasyVulkan::Initializer;

Instance::Instance(vector<const char *> extensions, vector<const char *> validation_layers) {
    setup_extensions(extensions);
    setup_validation_layers(validation_layers);

    LOGI("Applied extensions size : %lu", _extensions.size());
    for(auto s : _extensions) {
        LOGI("Applied extension : %s\n", s);
    }

    LOGI("Applied validation layers size : %lu", _validation_layers.size());
    for(auto s : _validation_layers) {
        LOGI("Applied validation layers : %s\n", s);
    }
}

Instance::~Instance() {
    if(_debug) {
        Debug::free_debug_callback(_instance);
    }

    if(_instance == VK_NULL_HANDLE) {
        return;
    }
    vkDestroyInstance(_instance, nullptr);
    _instance = VK_NULL_HANDLE;
}

void Instance::setup_extensions(vector<const char *> &requests) {
    vector<VkExtensionProperties> properties = Utility::enumerate_instance_extensions();

#ifdef __APPLE__
    _extensions.push_back("VK_KHR_portability_enumeration");
    _extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    _extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif 

    for(auto request : requests) {
        bool found = false;
        for(auto& prop : properties) {
            if(strcmp(request, prop.extensionName)==0) {
                _extensions.push_back(request);
                found = true;
                break;
            }
        }

        if(!found) {
            LOGI("Instance extension %s not supported.", request);
        }
    }
}

void Instance::setup_validation_layers(vector<const char *> &requests) {
    vector<VkLayerProperties> properties = Utility::enumerate_instance_layers();

    for(auto &request : requests) {
        bool found = false;
        for(auto prop : properties) {
            if(strcmp(request, prop.layerName)==0) {
                _validation_layers.push_back(request);
                found = true;
                break;
            }
        }

        if(!found) {
            LOGI("Instance Layer %s not supported.", request);
        }
    }

    
}

void Instance::create(ApplicationInfo *app_info, VkInstanceCreateFlags flags) {
    auto builder = new InstanceCreateInfo();
#ifdef __APPLE__
    flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
    const char *validation_layer_name = "VK_LAYER_KHRONOS_validation";

    if(_debug) {
        _extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        auto supported_layers = Utility::enumerate_instance_layers();

        bool present = false;
        for(auto layer : supported_layers) {
            if(strcmp(layer.layerName, validation_layer_name) == 0) {
                _validation_layers.push_back(validation_layer_name);
                present = true;
                break;
            }
        }

        if(!present) {
            LOGE("%s not present, validation is disabled.", validation_layer_name);
        }

        builder->validation_layers(_validation_layers);
    }

    builder->application_info(app_info)
        ->device_extensions(_extensions)
        ->flags(flags);
    
    VkInstanceCreateInfo info = builder->build();

    LOGD("[Instance::create] VkInstanceCreateInfo applicationInfo.appName : %s", info.pApplicationInfo->pApplicationName);
    LOGD("[Instance::create] VkInstanceCreateInfo applicationInfo.engineName : %s", info.pApplicationInfo->pEngineName);
    LOGD("[Instance::create] VkInstanceCreateInfo extensionCount : %d", info.enabledExtensionCount);
    LOGD("[Instance::create] VkInstanceCreateInfo layersCount : %d", info.enabledLayerCount);

    for(int i = 0 ; i < _extensions.size() ; i++) {
        LOGD("[Instance::create] VkInstanceCreateInfo extension name : %s", info.ppEnabledExtensionNames[i]);
    }

    for(int i = 0 ; i < _validation_layers.size() ; i++) {
        LOGD("[Instance::create] VkInstanceCreateInfo layer name : %s", info.ppEnabledLayerNames[i]);
    }

    CHECK_VK_RESULT( vkCreateInstance(&info, nullptr, &_instance) );
    
    if(_debug) {
        // LOGI("[Instance::create] DebugMessenger set.");
        Debug::setup_debugging(_instance);
    }

    delete builder;
}

VkInstance Instance::instance() {
    return _instance;
}

vector<const char *> Instance::extensions() {
    return _extensions;
}

vector<const char *> Instance::validation_layers() {
    return _validation_layers;
}

void Instance::set_debug(bool value) {
    if(_instance != VK_NULL_HANDLE) {
        LOGE("Impossible to change debug mode after VkInstance is created.")
        return;
    }

    _debug = value;
}

bool Instance::debug() {
    return _debug;
}

#endif