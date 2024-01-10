#ifndef __EV_PIPELINE_LAYOUT_H__
#define __EV_PIPELINE_LAYOUT_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <algorithm>
#include "base/ev_device_base.h"
#include "ev_descriptor_set_layout.h"
#include "ev_device.h"

using namespace std;

namespace EasyVulkan {

    class PipelineLayout : DeviceBase {
        
        VkPipelineLayout _layout = VK_NULL_HANDLE;

        vector<DescriptorSetLayout *> _descriptor_set_layouts;

        vector<VkPushConstantRange> _constants;

        public :
        
        explicit PipelineLayout(Device *device);

        ~PipelineLayout();

        VkResult create();

        void set_descriptor_set_layouts(vector<DescriptorSetLayout *> layouts);

        void add_constant(VkPushConstantRange range);

        void add_constants(vector<VkPushConstantRange> ranges);

        VkPipelineLayout layout();

        VkPipelineLayout& layout_alias();

        VkPipelineLayout* layout_ptr();

        void destroy();
    };
}

#endif