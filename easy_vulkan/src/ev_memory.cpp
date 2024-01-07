#ifndef __EV_MEMORY_CPP__
#define __EV_MEMORY_CPP__

#include <vulkan/vulkan.h>
#include "initializer/ev_memory_ai.h"
#include "ev_memory.h"

using namespace EasyVulkan;
    
Memory::Memory(Device *device) : _device(device) {
    
}

Memory::~Memory() {
    release();
}

void Memory::release() {
    if(_memory == VK_NULL_HANDLE) {
        return;
    }

    vkFreeMemory(_device->device(), _memory, nullptr);
}


VkResult Memory::allocate(MemoryAllocateInfo *info) {
    auto ci = info->build();
    auto ret = vkAllocateMemory(_device->device(), &ci, nullptr, &_memory);

    if(ret == VK_SUCCESS) {
        _memory_type_bit = ci.memoryTypeIndex;
        _size = ci.allocationSize;
        _flags = info->flags;
    }

    return ret;
}

Device* Memory::device() {
    return _device;
}

VkDeviceMemory Memory::memory() {
    return _memory;
}

VkDeviceSize Memory::size() {
    return _size;
}

VkMemoryPropertyFlags Memory::flags() {
    return _flags;
}

uint32_t Memory::type() {
    return _memory_type_bit;
}

#endif