#ifndef __EV_DEVICE_CPP__
#define __EV_DEVICE_CPP__

#include "ev_device.h"

using namespace EasyVulkan;
using namespace std;

bool Device::is_support_extension(const string extension_name) {
    return find(_supported_extensions.begin(), _supported_extensions.end(), extension_name) != _supported_extensions.end();
}

uint32_t Device::get_queue_family_index(VkQueueFlags flags) const {
    if((flags & VK_QUEUE_COMPUTE_BIT) == flags) {
        for(uint32_t i = 0 ; i < static_cast<uint32_t>(_queue_family_properties.size()) ; i++) {
            auto &family = _queue_family_properties[i].queueFlags;

            if((family & VK_QUEUE_COMPUTE_BIT) 
                && ((family & VK_QUEUE_GRAPHICS_BIT) == 0) ) {
                return i;
            }
        }
    }

    if((flags & VK_QUEUE_TRANSFER_BIT) == flags) {
        for(uint32_t i = 0 ; i < static_cast<uint32_t>(_queue_family_properties.size()) ; i++) {
            auto &family = _queue_family_properties[i].queueFlags;

            if((family & VK_QUEUE_COMPUTE_BIT) 
                && ((family & VK_QUEUE_GRAPHICS_BIT) == 0)
                && ((family & VK_QUEUE_COMPUTE_BIT) == 0)) {
                return i;
            }
        }
    }

    for(uint32_t i = 0 ; i < static_cast<uint32_t>(_queue_family_properties.size()) ; i++) {
        auto &family = _queue_family_properties[i].queueFlags;

        if((family & flags) == flags) {
            return i;
        }
    }

    throw std::runtime_error("Could not found a matching type queue family index");
}

Device::Device(Instance *_instance, uint32_t gpu_id) 
: instance(_instance) {
    LOGI("EasyVulkan Device create start.")
    vector<VkPhysicalDevice> gpus = Utility::enumerate_physical_devices(instance->instance());

    if(gpus.size() < 1) {
        throw runtime_error("No Vulkan Support Devices");
    }

    if(gpu_id > static_cast<uint32_t>(gpus.size())) {
        throw runtime_error("Invalid GPU ID");
    }

    gpu = gpus[gpu_id];

    _queue_family_properties = Utility::enumerate_queue_families(gpu);
    
    LOGI("EasyVulkan PhysicalDevice queue family properties get.")
    vkGetPhysicalDeviceProperties(gpu, &_device_properties);
    LOGI("EasyVulkan PhysicalDevice device properties get.")
    vkGetPhysicalDeviceMemoryProperties(gpu, &_memory_properties);
    LOGI("EasyVulkan PhysicalDevice memory properties get.")
    vkGetPhysicalDeviceFeatures(gpu, &_features);
    auto extensions = Utility::enumerate_device_extensions(gpu);
    LOGI("EasyVulkan PhysicalDevice extensions get.")

    for(auto extension : extensions) {
        _supported_extensions.push_back(extension.extensionName);
    }
}

Device::~Device() {
    if(_device != VK_NULL_HANDLE) {
        return ;
    }

    vkDestroyDevice(_device, nullptr);
}

void Device::create_logical_device(
    VkPhysicalDeviceFeatures enabled_features, 
    vector<char *> enabled_extensions,
    VkQueueFlags queue_types, 
    void* next, 
    bool use_swapchain) {
    
    if(_device != VK_NULL_HANDLE) {
        return ;
    }

    vector<Info::QueueCreateInfo*> queue_create_infos;
    Info::DeviceCreateInfo* device_ci = new Info::DeviceCreateInfo();

    if(queue_types & VK_QUEUE_GRAPHICS_BIT) {
        _queue_family_indices.graphics = get_queue_family_index(VK_QUEUE_GRAPHICS_BIT);
        auto *ci = new Info::QueueCreateInfo();
        ci = ci->queue_count(1)
        ->queue_index(_queue_family_indices.graphics);
        queue_create_infos.push_back(ci);
    } else {
        _queue_family_indices.graphics = 0;
    }

    if(queue_types & VK_QUEUE_COMPUTE_BIT) {
        _queue_family_indices.compute = get_queue_family_index(VK_QUEUE_COMPUTE_BIT);
        auto *ci = new Info::QueueCreateInfo();
        ci = ci->queue_count(1)
        ->queue_index(_queue_family_indices.compute);
        queue_create_infos.push_back(ci);
    } else {
        _queue_family_indices.compute = _queue_family_indices.graphics;
    }

    if(queue_types & VK_QUEUE_TRANSFER_BIT) {
        _queue_family_indices.transfer = get_queue_family_index(VK_QUEUE_TRANSFER_BIT);
        auto *ci = new Info::QueueCreateInfo();
        ci = ci->queue_count(1)
        ->queue_index(_queue_family_indices.transfer);
        queue_create_infos.push_back(ci);
    } else {
        _queue_family_indices.transfer = _queue_family_indices.graphics;
    }

    vector<char*> device_extensions(enabled_extensions);

    if(use_swapchain) {
        device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    VkPhysicalDeviceFeatures2 physical_device_features2 = {};

    if(next) {
        physical_device_features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        physical_device_features2.features = enabled_features;
        physical_device_features2.pNext = next;
        device_ci->next(&physical_device_features2);
    }

#if defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_KHR_portability_subset)
    if(is_support_extension(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME)) {
        device_extensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
    }
#endif

    for(auto extension : device_extensions) {
        if(!is_support_extension(extension)) {
            LOGE("Device extension : %s is not supported on this device.", extension);
        }
    }

    VkDeviceCreateInfo device_create_info = device_ci->enabled_extensions(device_extensions)
        ->enabled_features(enabled_features)
        ->queue_create_info(queue_create_infos)
        ->next(next)
        ->build();

    CHECK_VK_RESULT(vkCreateDevice(gpu, &device_create_info, nullptr, &_device));

    _enabled_features = enabled_features;

    for(auto *queue_create_info : queue_create_infos) {
        delete queue_create_info;
    }

    delete device_ci;
}

VkPhysicalDevice Device::physical_device() {
    return gpu;
}

VkDevice Device::device() {
    return _device;
}

VkPhysicalDeviceFeatures Device::features() {
    return _features;
}

VkPhysicalDeviceFeatures Device::enabled_features() {
    return _enabled_features;
}

vector<string> Device::supported_extensions() {
    return _supported_extensions;
}

VkFormat Device::get_supported_depth_format(bool check_sampling) {
    vector<VkFormat> depth_formats = { VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D16_UNORM_S8_UINT, VK_FORMAT_D16_UNORM };

    for(auto format : depth_formats) {
        VkFormatProperties properties;
        vkGetPhysicalDeviceFormatProperties(gpu, format, &properties);
        
        if(properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            if(check_sampling) {
                if(!(properties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) ) {
                    continue;
                }
            }
            return format;
        }
    }

    throw runtime_error("Could not find a suitable depth format.");
}

#endif