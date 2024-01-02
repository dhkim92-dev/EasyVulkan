#ifndef __EV_DEVICE_CI_H__
#define __EV_DEVICE_CI_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <algorithm>
#include "ev_utility.h"
#include "builder/ev_queue_ci.h"

using namespace std;

namespace EasyVulkan{
    namespace Info {
        class DeviceCreateInfo {

            // VkDeviceCreateFlags _flags = VK_FLAGS_NONE;

            void *_next = NULL;

            vector<char *> _enabled_extensions;

            VkPhysicalDeviceFeatures _enabled_features;

            vector<QueueCreateInfo *> _queue_ci;

            public:

            DeviceCreateInfo* enabled_extensions(vector<char *> values);

            DeviceCreateInfo* enabled_features(VkPhysicalDeviceFeatures value);

            DeviceCreateInfo* next(void *value);

            // DeviceCreateInfo* device_create_flags(VkDeviceCreateFlags value);

            DeviceCreateInfo* queue_create_info(vector<QueueCreateInfo *> value);

            VkDeviceCreateInfo build();
        };
    }
}

#endif