#ifndef __EV_DESCRIPTOR_POOL_H__
#define __EV_DESCRIPTOR_POOL_H__

#include <vulkan/vulkan.h>
#include <unordered_map>
#include <vector>
#include "base/ev_device_base.h"

using namespace std;

namespace EasyVulkan {

    class DescriptorPool : public DeviceBase {

        VkDescriptorPool _descriptor_pool = VK_NULL_HANDLE;

        unordered_map<VkDescriptorType, uint32_t> _reservation;

        public :

        DescriptorPool(Device *device);

        ~DescriptorPool();

        VkResult create(uint32_t max_sets, VkDescriptorPoolCreateFlags flags = 0, void *pNext = nullptr);

        void reserve(VkDescriptorType type, uint32_t count);

        VkDescriptorPool pool();

        VkDescriptorPool& pool_alias();

        VkDescriptorPool* pool_ptr();

        void destroy();
    };
}

#endif