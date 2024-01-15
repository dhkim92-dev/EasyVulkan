#ifndef __EV_IMAGE_H__
#define __EV_IMAGE_H__

#include <vulkan/vulkan.h>
#include <cassert>
#include "ev_device.h"
#include "ev_memory.h"

using namespace EasyVulkan;

namespace EasyVulkan {
    
    class Image : public DeviceBase {

        VkImage _image = VK_NULL_HANDLE;

        VkImageView _view = VK_NULL_HANDLE;   

        VkSampler _sampler = VK_NULL_HANDLE;

        Memory *_memory = nullptr;

        VkImageType _type;

        VkFormat _format;

        VkMemoryRequirements _memory_requirements;

        uint32_t _width;

        uint32_t _height;

        uint32_t _depth;

        VkDeviceSize _size;

        uint32_t _layers=1;
        
        VkImageTiling _tiling;

        VkImageLayout _layout = VK_IMAGE_LAYOUT_UNDEFINED;

        VkSampleCountFlagBits _samples = VK_SAMPLE_COUNT_1_BIT;

        VkImageUsageFlags _usage;

        uint32_t _mip_level = 1;

        public : 

        explicit Image(Device *device);

        ~Image();

        VkResult create_image(VkImageCreateInfo *info);

        VkResult create_view(VkImageViewCreateInfo *info);

        VkResult create_sampler(VkSamplerCreateInfo *info);

        VkResult bind(Memory *memory, VkDeviceSize offset=0);

        VkImage image() const; 

        VkImageView view() const;

        VkSampler sampler() const;

        Memory* memory();

        VkImage* image_ptr();

        VkImageView* view_ptr();

        VkSampler* sampler_ptr();

        uint32_t width() const;

        uint32_t* width_ptr();

        uint32_t height() const;

        uint32_t* height_ptr();

        uint32_t depth() const;

        uint32_t array_layers() const;

        VkImageTiling tiling() const;

        VkImageLayout layout() const;

        VkSampleCountFlagBits samples() const;

        VkImageUsageFlags usage() const;

        uint32_t mip_level() const;

        VkMemoryRequirements memory_requirements() const;

        void destroy();
    };
}

#endif