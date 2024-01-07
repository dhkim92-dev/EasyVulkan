#ifndef __EV_PHYSICAL_DEVICE_H__
#define __EV_PHYSICAL_DEVICE_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <cassert>
#include <algorithm>
#include "builder/ev_queue_ci.h"
#include "builder/ev_device_ci.h"
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

        VkPhysicalDevice gpu = VK_NULL_HANDLE;

        VkDevice _device = VK_NULL_HANDLE;

        VkPhysicalDeviceProperties _device_properties;

        VkPhysicalDeviceFeatures _features;

        VkPhysicalDeviceFeatures _enabled_features;
        
        VkPhysicalDeviceMemoryProperties _memory_properties;

        vector<string> _supported_extensions;

        vector<VkQueueFamilyProperties> _queue_family_properties;

        QueueFamilyIndice _queue_family_indices;

        bool is_support_extension(const string extension_name);

        uint32_t get_queue_family_index(VkQueueFlags flags) const;

        public :

        
        explicit Device(Instance *_instance, uint32_t gpu_id = 0);

        ~Device();

        void create_logical_device(VkPhysicalDeviceFeatures enabled_features, vector<const char *> enabled_extensions, VkQueueFlags queue_types = VK_QUEUE_GRAPHICS_BIT, void *next = nullptr, bool use_swapchain = true);

        VkPhysicalDevice physical_device();

        VkDevice device();

        VkPhysicalDeviceFeatures features();

        VkPhysicalDeviceFeatures enabled_features();

        VkPhysicalDeviceProperties device_properties();

        VkPhysicalDeviceMemoryProperties memory_properties();

        vector<VkQueueFamilyProperties> queue_family_properties();

        vector<string> supported_extensions();

        VkFormat get_supported_depth_format(bool check_sampling);

        uint32_t get_memory_type(uint32_t type_bits, VkMemoryPropertyFlags properties, VkBool32 *found) const;
    };
}

#endif