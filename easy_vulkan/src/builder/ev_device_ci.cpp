#ifndef __EV_DEVICE_CI_CPP__
#define __EV_DEVICE_CI_CPP__

#include "builder/ev_device_ci.h"

using namespace EasyVulkan::Info;

DeviceCreateInfo* DeviceCreateInfo::enabled_extensions(vector<char *> values) {
    std::copy(values.begin(), values.end(), back_inserter(_enabled_extensions));

    return this;
}

DeviceCreateInfo* DeviceCreateInfo::enabled_features(VkPhysicalDeviceFeatures value) {
    _enabled_features = value;

    return this;
}

DeviceCreateInfo* DeviceCreateInfo::next(void *value) {
    _next = value;
    
    return this;
}

// DeviceCreateInfo* DeviceCreateInfo::device_create_flags(VkDeviceCreateFlags value) {
    // _flags = value;

    // return this;
// }

DeviceCreateInfo* DeviceCreateInfo::queue_create_info(vector<QueueCreateInfo *> values) {
    std::copy(values.begin(), values.end(), back_inserter(_queue_ci));
    return this;
}

/**
 * @brief build a struct VkDeviceCreateInfo.
 * @details enabledLayerCount and ppEnabledLayerNames is ignored
 * because it is deprecated on Vulkan 1.3
 * @return {VkDeviceCreateInfo}
*/
VkDeviceCreateInfo DeviceCreateInfo::build() {
    vector<VkDeviceQueueCreateInfo> q_cis;
    
    for(auto ci : _queue_ci) {
        q_cis.push_back(ci->build());
    }

    VkDeviceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    if(!_enabled_extensions.empty()) {
        info.enabledExtensionCount=static_cast<uint32_t>(_enabled_extensions.size());
        info.ppEnabledExtensionNames = _enabled_extensions.data();
    }

    info.pEnabledFeatures = &_enabled_features;
    info.queueCreateInfoCount = static_cast<uint32_t>(q_cis.size());
    info.pQueueCreateInfos = q_cis.data();
    info.pNext = _next;

    // deprecated
    // info.enabledLayerCount = 0;
    // info.ppEnabledLayerNames = nullptr;

    return info;
}


#endif