#ifndef __EV_DESCRIPTOR_POOL_CPP__
#define __EV_DESCRIPTOR_POOL_CPP__

#include "ev_descriptor_pool.h"

using namespace EasyVulkan;

DescriptorPool::DescriptorPool(Device *device) : DeviceBase(device) {
}

DescriptorPool::~DescriptorPool() {
    destroy();
}

VkResult DescriptorPool::create(uint32_t max_sets, VkDescriptorPoolCreateFlags flags, void* next) {
    if(_descriptor_pool != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }
    
    vector<VkDescriptorPoolSize> sizes;

    for(auto iter = _reservation.begin() ; iter != _reservation.end() ; iter++) {
        auto type = iter->first;
        auto count = iter->second;
        
        sizes.push_back({type, count});
    }

    if(sizes.empty()) {
        LOGE("DescriptorPoolSize should be more than 1.");
        return VK_INCOMPLETE;
    }

    VkDescriptorPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = flags;
    info.maxSets = max_sets;
    info.poolSizeCount = static_cast<uint32_t>(sizes.size());
    info.pPoolSizes = sizes.data();

    return vkCreateDescriptorPool(_device->device(), &info, nullptr, &_descriptor_pool);
}

void DescriptorPool::reserve(VkDescriptorType type, uint32_t count) {
    if(_descriptor_pool != VK_NULL_HANDLE) {
        LOGE("Can not reserve on already initialized Descriptor pool.")
        return;
    }

    _reservation[type] += count;
}

VkDescriptorPool DescriptorPool::pool() {
    return _descriptor_pool;
}

VkDescriptorPool& DescriptorPool::pool_alias() {
    return _descriptor_pool;
}

VkDescriptorPool* DescriptorPool::pool_ptr() {
    return &_descriptor_pool;
}

void DescriptorPool::destroy() {
    if(_descriptor_pool == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyDescriptorPool(_device->device(), _descriptor_pool, nullptr);
    _descriptor_pool = VK_NULL_HANDLE;
}

#endif