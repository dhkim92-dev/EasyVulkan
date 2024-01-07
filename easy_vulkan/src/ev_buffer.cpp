#ifndef __EV_BUFFER_CPP__
#define __EV_BUFFER_CPP__

#include <memory.h>
#include "ev_buffer.h"

using namespace EasyVulkan;

// Constructor & Destructor
Buffer::Buffer(Device *device) {
    _device = device;
}

Buffer::Buffer(Device *device, BufferCreateInfo* buffer_ci) {
    _device = device;
    create_buffer(buffer_ci);
}

Buffer::~Buffer() {
    destroy();
}

// Public Methods
VkResult Buffer::create_buffer(BufferCreateInfo* buffer_ci) {
    auto ci = buffer_ci->build();
    auto ret = vkCreateBuffer(_device->device(), &ci, nullptr, &_buffer);

    if(ret == VK_SUCCESS) {
        vkGetBufferMemoryRequirements(_device->device(), _buffer, &_memory_requirements);
        _usage = ci.usage;
        _size = ci.size;
        _alignment = _memory_requirements.alignment;
    }

    return ret;
}

/**
 * @brief copy data to buffer memory
*/
void Buffer::copy(void *src, VkDeviceSize size) {
    assert(mapped);
    if(mapped == nullptr) {
        LOGE("Need memory mapping before copy.");
        return ;
    }
    memcpy(mapped, src, size);
}

/**
 * @brief copy data from buffer to host memory
*/
void Buffer::dump(void *dst, VkDeviceSize size) {
    assert(mapped);
    assert(dst);
    memcpy(dst, mapped, size);
}


VkResult Buffer::map(VkDeviceSize offset, VkDeviceSize size) {
    assert(_memory != nullptr);
    return vkMapMemory(_device->device(), _memory->memory(), _offset + offset, size, 0, &mapped);
}

void Buffer::unmap() {
    assert(_memory != nullptr);
    if(mapped) {
        vkUnmapMemory(_device->device(), _memory->memory());
        mapped = nullptr;
    }
}

VkResult Buffer::bind(Memory *memory, VkDeviceSize offset) {
    assert(memory != nullptr);
    _offset = offset;
    _memory = memory;
    vkBindBufferMemory(_device->device(), _buffer, _memory->memory(), offset);
}

VkResult Buffer::flush(VkDeviceSize offset, VkDeviceSize size) {
    VkMappedMemoryRange range{};
    range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    range.memory = _memory->memory();
    range.offset = offset;
    range.size = size;
    range.pNext = nullptr;

    return vkFlushMappedMemoryRanges(_device->device(), 1, &range);
}

VkResult Buffer::invalidate(VkDeviceSize offset, VkDeviceSize size) {
    VkMappedMemoryRange range{};
    range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    range.memory = _memory->memory();
    range.offset = offset;
    range.size = size;
    range.pNext = nullptr;

    return vkInvalidateMappedMemoryRanges(_device->device(), 1, &range);
}

void Buffer::destroy() {
    if(_buffer == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyBuffer(_device->device(), _buffer, nullptr);
}

VkBuffer Buffer::buffer() {
    return _buffer;
}

Memory* Buffer::memory() {
    return _memory;
}

VkDeviceSize Buffer::offset() {
    return _offset;
}

VkDeviceSize Buffer::size() {
    return _size;
}

VkDeviceSize Buffer::alignment() {
    return _alignment;
}

VkBufferUsageFlags Buffer::usage() {
    return _usage;
}

VkMemoryRequirements Buffer::memory_requirements() {
    return _memory_requirements;
}

#endif