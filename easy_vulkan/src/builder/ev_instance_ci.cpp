#ifndef __EV_INSTANCE_CI_CPP__
#define __EV_INSTANCE_CI_CPP__

#include "builder/ev_instance_ci.h"

using namespace EasyVulkan::Info;

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

InstanceCreateInfo* InstanceCreateInfo::device_extensions(vector<const char *> value) {
    copy( value.begin(), value.end(), back_inserter(extensions));

    return this;
}

InstanceCreateInfo* InstanceCreateInfo::validation_layers(vector<const char *> value) {
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
    vk_app_info = app_info->build();

    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
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