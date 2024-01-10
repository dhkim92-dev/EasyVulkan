#ifndef __EV_DESCRIPTOR_SET_LAYOUT_CPP__
#define __EV_DESCRIPTOR_SET_LAYOUT_CPP__

#include "ev_descriptor_set_layout.h"

using namespace EasyVulkan;

DescriptorSetLayout::DescriptorSetLayout(Device *device) : DeviceBase(device) {
}

DescriptorSetLayout::~DescriptorSetLayout() {
    destroy();
}

VkResult DescriptorSetLayout::create() {
    if(_layout != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }

    VkDescriptorSetLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.bindingCount = static_cast<uint32_t>(_binding.size());
    info.pBindings = _binding.data();

    return vkCreateDescriptorSetLayout(_device->device(), &info, nullptr, &_layout);
}

void DescriptorSetLayout::bind(VkShaderStageFlags stage, uint32_t bind_no, VkDescriptorType type, uint32_t count, VkSampler *sampler_ptr) {
    if(_layout != VK_NULL_HANDLE) {
        LOGE("Can not update resource since DescriptorSetLayout created.");
        return;
    }

    VkDescriptorSetLayoutBinding layout_binding {};
    layout_binding.binding = bind_no;
    layout_binding.descriptorCount = count;
    layout_binding.descriptorType = type;
    layout_binding.pImmutableSamplers = sampler_ptr;
    layout_binding.stageFlags = stage;

    _binding.push_back(layout_binding);    
}

VkDescriptorSetLayout DescriptorSetLayout::layout() {
    return _layout;
}

VkDescriptorSetLayout& DescriptorSetLayout::layout_alias() {
    return _layout;
}

VkDescriptorSetLayout* DescriptorSetLayout::layout_ptr() {
    return &_layout;
}

void DescriptorSetLayout::destroy() {
    if(_layout == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyDescriptorSetLayout(_device->device(), _layout, nullptr);
    _layout = VK_NULL_HANDLE;
}

#endif