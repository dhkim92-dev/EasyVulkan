#ifndef __EV_FENCE_CPP__
#define __EV_FENCE_CPP__

#include "ev_fence.h"

using namespace EasyVulkan;

Fence::Fence(Device *device) : DeviceBase(device) {
    create();
}

VkResult Fence::create() {
    if(_fence != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }

    VkFenceCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    info.pNext = nullptr;

    return vkCreateFence(_device->device(), &info, nullptr, &_fence);
}

void Fence::destroy() {
    if(_fence == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyFence(_device->device(), _fence, nullptr);
}

VkFence Fence::fence() {
    return _fence;
}

#endif