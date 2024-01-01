#ifndef __EV_PHYSICAL_DEVICE_H__
#define __EV_PHYSICAL_DEVICE_H__

#include <vulkan/vulkan.h>
#include <vector>
#include "ev_instance.h"
#include "ev_utility.h"

using namespace std;

namespace EasyVulkan {

    struct QueueFamilyIndice {
        uint32_t graphics;
        uint32_t compute;
        uint32_t transfer;
    };

    class Device{
        
        Instance *instance;

        VkPhysicalDevice gpu = NULL;

        VkDevice device = NULL;

        VkPhysicalDeviceProperties properties;

        VkPhysicalDeviceFeatures features;

        VkPhysicalDeviceFeatures enabled_features;

        vector<char *> extensions;

        vector<char *> enabled_extensions;


        public :
        
        explicit Device(Instance *instance, vector<char *> _extensions, uint32_t gpu_id = 0);
    }
}

#endif