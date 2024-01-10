#ifndef __EV_QUEUE_CPP__
#define __EV_QUEUE_CPP__

#include "ev_queue.h"

using namespace EasyVulkan;

CommandQueue::CommandQueue(Device *device, VkQueueFlags flags): DeviceBase(device) {
    _queue_family_index = _device->get_queue_family_index(flags);
}

CommandQueue::~CommandQueue() {
}

void CommandQueue::create() {
    if(_queue != VK_NULL_HANDLE) return;
    vkGetDeviceQueue(_device->device(), _queue_family_index, _queue_index, &_queue);
}

VkResult CommandQueue::submit(SubmitInfo *submit_info, Fence *fence) {
    auto info = submit_info->build();
    VkFence _fence = fence ? fence->fence() : nullptr;
    return vkQueueSubmit(_queue, 1, &info, _fence);
}

// getter

VkQueue CommandQueue::queue() {
    return _queue;
}

VkQueue& CommandQueue::queue_alias() {
    return _queue;
}

VkQueue* CommandQueue::queue_ptr() {
    return &_queue;
}

uint32_t CommandQueue::queue_index() {
    return _queue_index;
}

uint32_t CommandQueue::queue_family_index() {
    return _queue_family_index;
}


#endif