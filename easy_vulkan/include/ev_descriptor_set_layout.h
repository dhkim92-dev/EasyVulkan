#ifndef __EV_DESCRIPTOR_SET_LAYOUT_H__
#define __EV_DESCRIPTOR_SET_LAYOUT_H__

#include <vulkan/vulkan.h>
#include <unordered_map>
#include <vector>
#include "base/ev_device_base.h"

using namespace std;

namespace EasyVulkan {

    class DescriptorSetLayout : DeviceBase {
        
        VkDescriptorSetLayout _layout = VK_NULL_HANDLE;

        vector<VkDescriptorSetLayoutBinding> _binding;

        public : 

        explicit DescriptorSetLayout(Device *device);

        ~DescriptorSetLayout();

        VkResult create();

        void bind(VkShaderStageFlags stage, uint32_t bind_no, VkDescriptorType type, uint32_t count = 1, VkSampler *sampler_ptr = nullptr);

        VkDescriptorSetLayout layout();

        VkDescriptorSetLayout& layout_alias();

        VkDescriptorSetLayout* layout_ptr();
        
        void destroy();
    };
}

#endif