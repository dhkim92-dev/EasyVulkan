#ifndef __EV_QUEUE_CI_CPP__
#define __EV_QUEUE_CI_CPP__

#include "initializer/ev_queue_ci.h"

using namespace EasyVulkan::Initializer;

QueueCreateInfo* QueueCreateInfo::queue_priorities(float value) {
    _priorities = value;

    return this;
}

QueueCreateInfo* QueueCreateInfo::queue_index(uint32_t value) {
    _index = value;   

    return this;
}

QueueCreateInfo* QueueCreateInfo::queue_count(uint32_t value) {
    _count = value;

    return this;
}

QueueCreateInfo* QueueCreateInfo::next(void *value) {
    _next = value;

    return this;
}

QueueCreateInfo* QueueCreateInfo::flags(VkDeviceQueueCreateFlags value) {
    _flags = value;

    return this;
}

VkDeviceQueueCreateInfo QueueCreateInfo::build() {
    VkDeviceQueueCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.flags = _flags;
    info.pNext = _next;
    info.queueCount = _count;
    info.pQueuePriorities = &_priorities;
    info.queueFamilyIndex = _index;

    return info;
}

#endif