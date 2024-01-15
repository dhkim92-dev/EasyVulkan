#ifndef __EV_IMAGE_CREATE_INFO_CPP__
#define __EV_IMAGE_CREATE_INFO_CPP__

#include "initializer/ev_image_ci.h"

using namespace EasyVulkan;

VkImageCreateInfo Initializer::image_create_info(uint32_t width, uint32_t height, uint32_t depth) {
    VkImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.extent =  {width, height, depth};
    info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.tiling = VK_IMAGE_TILING_OPTIMAL;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.format = VK_FORMAT_R8G8B8A8_SRGB;
    info.imageType = VK_IMAGE_TYPE_2D;
    info.arrayLayers = 1;
    info.mipLevels = 1;

    return info;
}

VkImageViewCreateInfo Initializer::image_view_create_info() {
    VkImageViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    return info;
}

VkSamplerCreateInfo Initializer::sampler_create_info() {
    VkSamplerCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.compareOp = VK_COMPARE_OP_NEVER;
    info.minFilter = VK_FILTER_LINEAR;
    info.magFilter = VK_FILTER_LINEAR;
    info.minLod = 0.0f;
    info.maxLod = 0.0f;

    return info;
}


#endif