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

Instance::Instance(vector<string> extensions, vector<string> validation_layers) {
    setup_extensions(extensions);
    setup_validation_layers(validation_layers);
}

Instance::~Instance() {
    vkDestroyInstance(_instance, nullptr);
}

void Instance::setup_extensions(vector<string> &requests) {
    vector<VkExtensionProperties> properties = Utility::enumerate_instance_extensions();

    for(auto request : requests) {
        bool found = false;
        for(auto prop : properties) {
            if(strcmp(request.c_str(), prop.extensionName)==0) {
                _extensions.push_back(prop.extensionName);
                found = true;
                break;
            }
        }

        if(!found) {
            LOGI("Instance extension %s not supported", request.c_str());
        }
    }
}

void Instance::setup_validation_layers(vector<string> &requests) {
    vector<VkLayerProperties> properties = Utility::enumerate_instance_layers();

    for(auto request : requests) {
        bool found = false;
        for(auto prop : properties) {
            if(strcmp(request.c_str(), prop.layerName)==0) {
                _validation_layers.push_back(prop.layerName);
                found = true;
                break;
            }
        }

        if(!found) {
            LOGI("Instance Layer %s not supported", request.c_str());
        }
    }
}

void Instance::create(ApplicationInfo *app_info, VkInstanceCreateFlags flags) {
    LOGD("Instance create start.");

    auto builder = new InstanceCreateInfo();
    
    VkInstanceCreateInfo info = builder
        ->application_info(app_info)
        ->device_extensions(_extensions)
        ->validation_layers(_validation_layers)
        ->flags(flags)
        ->build();

    CHECK_VK_RESULT( vkCreateInstance(&info, nullptr, &_instance) );
    delete builder;
    LOGD("Instance create end.");
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
    copy( value.begin(), value.end(), extensions.begin() );
    return this;
}

InstanceCreateInfo* InstanceCreateInfo::validation_layers(vector<char *> value) {
    copy(value.begin(), value.end(), validations.begin());
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

    if(app_info == nullptr) {
        LOGE("ApplicationInfo is not provided.")
    }

    VkApplicationInfo vk_app_info = app_info->build();
    info.pApplicationInfo = &vk_app_info;

    if(!extensions.empty()) {
        info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        info.ppEnabledExtensionNames = extensions.data();
    }

    if(!validations.empty()) {
        info.enabledLayerCount = static_cast<uint32_t>(validations.size());
        info.ppEnabledLayerNames = validations.data();
    }

    if(_flags > 0) {
        info.flags = _flags;
    }

    info.pNext = _next;

    return info;
}


#endif