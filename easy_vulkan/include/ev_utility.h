#ifndef __EV_UTILITY_H__
#define __EV_UTILITY_H__

#include <cstdio>
#include <cassert>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

using namespace std;

#define VK_FLAGS_NONE 0

#define CHECK_VK_RESULT(f)          \
{                                   \
    VkResult res = (f);             \
    if(res != VK_SUCCESS) {         \
        cout << "[FATAL] [" << __FILE__ << ":" << __LINE__ << "] : " << "VkResult is \"" << EasyVulkan::Utility::error_code(res) << "\"\n"; \
        assert(res == VK_SUCCESS);  \
    }                               \
} 

#ifndef NDEBUG
    #define LOGD(...)   \
    {    \
        cout << "[DEBUG] [" << __FILE__ << ":" << __LINE__ << "] - ";   \
        printf(__VA_ARGS__);    \
        cout << "\n";    \
    };
#else
    #define LOGD(...) 
#endif

#define LOGE(...)    \
{    \
    cerr << "[ERROR] [" << __FILE__ << ":" << __LINE__ << "] - ";    \
    printf(__VA_ARGS__);    \
    cerr << "\n";    \
}

#define LOGI(...)    \
{    \
    cout << "[INFO] [" __FILE__ << ":" << __LINE__<< "] - ";    \
    printf(__VA_ARGS__);    \
    cout << "\n";    \
}

#define LOGV(...)    \
{    \
    cout << "[VERBOSE] [" __FILE__ << ":" << __LINE__<< "] - ";    \
    printf(__VA_ARGS__);    \
    cout << "\n";    \
}

#define LOGW(...)    \
{    \
    cout << "[WARNING] [" __FILE__ << ":" << __LINE__<< "] - ";    \
    printf(__VA_ARGS__);    \
    cout << "\n";    \
}



namespace EasyVulkan {
    namespace Utility {

        string error_code(VkResult error);

        string physical_device_type(VkPhysicalDeviceType type);

        vector<VkExtensionProperties> enumerate_instance_extensions();

        vector<VkPhysicalDevice> enumerate_physical_devices(VkInstance instance);

        vector<VkLayerProperties> enumerate_instance_layers();

        vector<VkQueueFamilyProperties> enumerate_queue_families(VkPhysicalDevice physical_device);

        vector<VkExtensionProperties> enumerate_device_extensions(VkPhysicalDevice physical_device);
    }
}


#endif