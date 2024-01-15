#ifndef __EV_IMAGE_CREATE_INFO_H__
#define __EV_IMAGE_CREATE_INFO_H__

#include <vulkan/vulkan.h>

namespace EasyVulkan {
    namespace Initializer {

        VkImageCreateInfo image_create_info(uint32_t width, uint32_t height, uint32_t depth);

        VkImageViewCreateInfo image_view_create_info();

        VkSamplerCreateInfo sampler_create_info();
    }
}

#endif