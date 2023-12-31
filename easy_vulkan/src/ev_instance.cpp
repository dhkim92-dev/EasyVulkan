#ifndef __EV_INSTANCE_CPP__
#define __EV_INSTANCE_CPP__

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <unordered_set>
#include "ev_instance.h"

using namespace std;
using namespace EasyVulkan;

Instance::Instance(vector<char *> extensions, vector<char *> validation_layers) {
    setup_extensions(extensions);

#ifndef NDEBUG
    setup_validation_layers(validation_layers);
#endif

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
    vkDestroyInstance(_instance, nullptr);
}

void Instance::setup_extensions(vector<char *> &requests) {
    vector<VkExtensionProperties> properties = Utility::enumerate_instance_extensions();

#ifdef __APPLE__
    _extensions.push_back("VK_KHR_portability_enumeration");
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

void Instance::setup_validation_layers(vector<char *> &requests) {
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
            LOGI("Instance Layer %s not supported.");
        }
    }

    
}

void Instance::create(ApplicationInfo *app_info, VkInstanceCreateFlags flags) {
    auto builder = new InstanceCreateInfo();
    LOGD("FLAG : %d\n", VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);
#ifdef __APPLE__
    flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
    
    builder=builder
        ->application_info(app_info)
        ->device_extensions(_extensions)
        ->validation_layers(_validation_layers)
        ->flags(flags);
    LOGD("builder flags : %d\n", flags)
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
    delete builder;
}

VkInstance Instance::instance() {
    return _instance;
}

vector<char *> Instance::extensions() {
    return _extensions;
}

vector<char *> Instance::validation_layers() {
    return _validation_layers;
}

ApplicationInfo* ApplicationInfo::api_version(uint32_t value) {
    _api_version = value;
    return this;
}

ApplicationInfo* ApplicationInfo::app_name(string value) {
    _app_name = value;
    return this;
}

ApplicationInfo* ApplicationInfo::app_version(uint32_t value) {
    _app_version = value;
    return this;
}

ApplicationInfo* ApplicationInfo::engine_name(string value) {
    _engine_name = value;
    return this;
}

ApplicationInfo* ApplicationInfo::engine_version(uint32_t value) {
    _engine_version = value;
    return this;
}

ApplicationInfo* ApplicationInfo::next(void *ptr) {
    _next = ptr;
    return this;
}

VkApplicationInfo ApplicationInfo::build() {
    VkApplicationInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.apiVersion = _api_version;
    info.applicationVersion = _app_version;
    info.engineVersion = _engine_version;
    info.pApplicationName = _app_name.c_str();
    info.pEngineName = _engine_name.c_str();
    info.pNext = _next;
    return info;
} 


InstanceCreateInfo* InstanceCreateInfo::application_info(ApplicationInfo *info) {
    app_info = info;
    return this;
}

InstanceCreateInfo* InstanceCreateInfo::device_extensions(vector<char *> value) {
    copy( value.begin(), value.end(), back_inserter(extensions));
    return this;
}

InstanceCreateInfo* InstanceCreateInfo::validation_layers(vector<char *> value) {
    copy(value.begin(), value.end(), back_inserter(validations));
    for(auto s : value) {
        printf("%s\n", s);
    }
    return this;
}

InstanceCreateInfo* InstanceCreateInfo::flags(VkInstanceCreateFlags value) {
    _flags = value;
    return this;
}

InstanceCreateInfo* InstanceCreateInfo::next(void *ptr) {
    _next = ptr;
    return this;
}

VkInstanceCreateInfo InstanceCreateInfo::build() {
    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    vk_app_info = app_info->build();
    info.pApplicationInfo = &vk_app_info;

    if(!extensions.empty()) {
        info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        info.ppEnabledExtensionNames = extensions.data();
    }

    if(!validations.empty()) {
        info.enabledLayerCount = static_cast<uint32_t>(validations.size());
        info.ppEnabledLayerNames = validations.data();
    }
    info.flags = _flags;
    info.pNext = _next;
    return info;
}


#endif