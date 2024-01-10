#ifndef __EV_DESCRIPTOR_SET_CPP__
#define __EV_DESCRIPTOR_SET_CPP__

#include "ev_descriptor_set.h"

using namespace EasyVulkan;

DescriptorSet::DescriptorSet(DescriptorPool *descriptor_pool, DescriptorSetLayout *layout) 
    : DeviceBase(descriptor_pool->device()), _layout(layout), _descriptor_pool(descriptor_pool) {
}

DescriptorSet::DescriptorSet(DescriptorPool *descriptor_pool, DescriptorSetLayout *layout, uint32_t count) 
    : DeviceBase(descriptor_pool->device()), _layout(layout), _descriptor_pool(descriptor_pool) {
    allocate(count);
}

DescriptorSet::~DescriptorSet() {
    destroy();
}

VkResult DescriptorSet::allocate(uint32_t count) {
    if(_descriptor_set != VK_NULL_HANDLE) {
        LOGE("Descriptor already allocated.");
        return VK_SUCCESS;
    }

    VkDescriptorSetAllocateInfo info{};
    info.descriptorPool = _descriptor_pool->pool();
    info.descriptorSetCount = count;
    info.pSetLayouts = _layout->layout_ptr();
    info.pNext = nullptr;
    _count = count;
    
    return vkAllocateDescriptorSets(_device->device(), &info, &_descriptor_set);
}

void DescriptorSet::destroy() {
    if(_descriptor_set == VK_NULL_HANDLE) {
        return;
    }

    vkFreeDescriptorSets(_device->device(), _descriptor_pool->pool(), _count, &_descriptor_set);
}

#endif