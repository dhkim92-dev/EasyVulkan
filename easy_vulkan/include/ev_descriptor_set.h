#ifndef __EV_DESCRIPTOR_SET_H__
#define __EV_DESCRIPTOR_SET_H__

#include <vulkan/vulkan.h>
#include "ev_device.h"
#include "ev_descriptor_set_layout.h"
#include "ev_descriptor_pool.h"
#include "base/ev_device_base.h"

using namespace std;

namespace EasyVulkan {

    class DescriptorSet : DeviceBase {

        VkDescriptorSet _descriptor_set = VK_NULL_HANDLE;

        DescriptorSetLayout* _layout = nullptr;

        DescriptorPool * _descriptor_pool = nullptr;

        uint32_t _count = 1;

        public :

        explicit DescriptorSet(DescriptorPool *descriptor_pool, DescriptorSetLayout *layout);

        explicit DescriptorSet(DescriptorPool *descriptor_pool, DescriptorSetLayout *layout, uint32_t count);

        ~DescriptorSet();

        VkResult allocate(uint32_t count);

        void destroy();

        VkDescriptorSet set();

        VkDescriptorSet& set_alias();

        VkDescriptorSet& set_ptr();
    };
}

#endif
