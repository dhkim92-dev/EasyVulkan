#ifndef __EV_BUFFER_CREATE_INFO_CPP__
#define __EV_BUFFER_CREATE_INFO_CPP__

#include "initializer/ev_buffer_ci.h"

using namespace EasyVulkan::Initializer;
BufferCreateInfo* BufferCreateInfo::flags(VkBufferCreateFlags value) {
    _flags = value;

    return this;
}

BufferCreateInfo* BufferCreateInfo::size(VkDeviceSize value) {
    _size = value;

    return this;
}

BufferCreateInfo* BufferCreateInfo::next(void *value) {
    _next = value;

    return this;
}


BufferCreateInfo* BufferCreateInfo::usage(VkBufferUsageFlags value) {
    _usage = value;

    return this;
}


BufferCreateInfo* BufferCreateInfo::sharing_mode(VkSharingMode value) {
    _sharing_mode = value;

    return this;
}

VkBufferCreateInfo BufferCreateInfo::build() {
    VkBufferCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    
    if(_flags != VK_FLAGS_NONE) {
        info.flags = _flags;
    }

    if(_sharing_mode == VK_SHARING_MODE_CONCURRENT) {
        info.pQueueFamilyIndices = _queue_family_indices;
        info.queueFamilyIndexCount = _queue_family_index_count;
    }

    info.pNext = _next;
    info.sharingMode = _sharing_mode;
    info.size = _size;
    info.usage = _usage;

    return info;
}

#endif