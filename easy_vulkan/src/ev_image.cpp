#ifndef __EV_IMAGE_CPP__
#define __EV_IMAGE_CPP__

#include "ev_image.h"

Image::Image(Device *device) : DeviceBase(device) {

}

Image::~Image() {
    destroy();
}

VkResult Image::create_image(VkImageCreateInfo *info) {
    if(_image != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }

    VkResult result = vkCreateImage(_device->device(), info, nullptr, &_image);

    if(result == VK_SUCCESS) {
        vkGetImageMemoryRequirements(_device->device(), _image, &_memory_requirements);
        _width = info->extent.width;
        _height = info->extent.height;
        _depth = info->extent.depth;
        _format = info->format;
        _layers = info->arrayLayers;
        _type = info->imageType;
        _tiling = info->tiling;
        _layout = info->initialLayout;
        _samples = info->samples;
        _usage = info->usage;
        _mip_level = info->mipLevels;
    }

    return result;
}

VkResult Image::create_view(VkImageViewCreateInfo *info) {
    assert(_memory != nullptr);
    info->image = _image;
    return vkCreateImageView(_device->device(), info, nullptr, &_view);
} 

VkResult Image::create_sampler(VkSamplerCreateInfo *info) {
    assert(_image != VK_NULL_HANDLE);
    return vkCreateSampler(_device->device(), info, nullptr, &_sampler);
}

VkResult Image::bind(Memory *memory, VkDeviceSize offset) {
    assert(memory != nullptr);

    VkResult result = vkBindImageMemory(_device->device(), _image, memory->memory(), offset);

    if(result == VK_SUCCESS) {
        _memory = memory;
    }

    return result;
}

VkImage Image::image() const {
    return _image;
}

VkImage* Image::image_ptr() {
    return &_image;
}

VkImageView Image::view() const {
    return _view;
}

Memory* Image::memory() {
    return _memory;
}

VkImageView* Image::view_ptr() {
    return &_view;
}

VkSampler Image::sampler() const {
    return _sampler;
}

VkSampler* Image::sampler_ptr() {
    return &_sampler;
}

uint32_t Image::width() const {
    return _width;
}

uint32_t* Image::width_ptr() {
    return &_width;
}

uint32_t Image::height() const {
    return _height;
}

uint32_t* Image::height_ptr() {
    return &_height;
}

uint32_t Image::depth() const {
    return _depth;
}

uint32_t Image::array_layers() const {
    return _layers;
}

VkImageTiling Image::tiling() const {
    return _tiling;
}

VkImageLayout Image::layout() const {
    return _layout;
}

VkSampleCountFlagBits Image::samples() const {
    return _samples;
}

VkImageUsageFlags Image::usage() const {
    return _usage;
}

VkMemoryRequirements Image::memory_requirements() const {
    return _memory_requirements;
}

uint32_t Image::mip_level() const {
    return _mip_level;
}

void Image::destroy() {
    if(_sampler != VK_NULL_HANDLE) {
        vkDestroySampler(_device->device(), _sampler, nullptr);
    }

    if(_view != VK_NULL_HANDLE) {
        vkDestroyImageView(_device->device(), _view, nullptr);
    }

    if(_image != VK_NULL_HANDLE) {
        vkDestroyImage(_device->device(), _image, nullptr);
    }

    _sampler = VK_NULL_HANDLE;
    _view = VK_NULL_HANDLE;
    _image = VK_NULL_HANDLE;
}

#endif