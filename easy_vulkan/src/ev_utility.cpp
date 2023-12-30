#ifndef __EV_UTILITY_CPP__
#define __EV_UTILITY_CPP__

#include "ev_utility.h"

using namespace std;
using namespace EasyVulkan;

string Utility::error_code(VkResult error) {
    switch(error) {
#define STR(r) case VK_ ##r: return #r
				STR(NOT_READY);
				STR(TIMEOUT);
				STR(EVENT_SET);
				STR(EVENT_RESET);
				STR(INCOMPLETE);
				STR(ERROR_OUT_OF_HOST_MEMORY);
				STR(ERROR_OUT_OF_DEVICE_MEMORY);
				STR(ERROR_INITIALIZATION_FAILED);
				STR(ERROR_DEVICE_LOST);
				STR(ERROR_MEMORY_MAP_FAILED);
				STR(ERROR_LAYER_NOT_PRESENT);
				STR(ERROR_EXTENSION_NOT_PRESENT);
				STR(ERROR_FEATURE_NOT_PRESENT);
				STR(ERROR_INCOMPATIBLE_DRIVER);
				STR(ERROR_TOO_MANY_OBJECTS);
				STR(ERROR_FORMAT_NOT_SUPPORTED);
				STR(ERROR_SURFACE_LOST_KHR);
				STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
				STR(SUBOPTIMAL_KHR);
				STR(ERROR_OUT_OF_DATE_KHR);
				STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
				STR(ERROR_VALIDATION_FAILED_EXT);
				STR(ERROR_INVALID_SHADER_NV);
#undef STR
        default :
            return "UNKOWN ERROR";
    }
}

string Utility::physical_device_type(VkPhysicalDeviceType type) {
    switch(type) {
#define STR(t) case VK_PHYSICAL_DEVICE_TYPE_ ##t: return #t
        STR(OTHER);
        STR(INTEGRATED_GPU);
        STR(DISCRETE_GPU);
        STR(VIRTUAL_GPU);
        STR(CPU);
#undef STR
        default :
            return "UNKNOWN DEVICE TYPE";
    }
}

vector<VkExtensionProperties> Utility::enumerate_instance_extensions() {
    uint32_t count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &count , nullptr);
    vector<VkExtensionProperties> properties(count);
    vkEnumerateInstanceExtensionProperties(nullptr, &count , properties.data());

    return properties;
}

vector<VkExtensionProperties> Utility::enuemrate_device_extensions(VkPhysicalDevice gpu) {
    uint32_t count = 0;
    vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
    vector<VkExtensionProperties> properties(count);
    vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, properties.data());

    return properties;
}

vector<VkPhysicalDevice> enumerate_physical_devices(VkInstance instance) {
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    vector<VkPhysicalDevice> gpus(count);
    vkEnumeratePhysicalDevices(instance, &count, gpus.data());

    return gpus;
}

vector<VkLayerProperties> Utility::enumerate_instance_layers() {
    uint32_t count = 0;
    vkEnumerateInstanceLayerProperties(&count, nullptr);
    vector<VkLayerProperties> properties(count);
    vkEnumerateInstanceLayerProperties(&count, properties.data());

    return properties;
}

#endif