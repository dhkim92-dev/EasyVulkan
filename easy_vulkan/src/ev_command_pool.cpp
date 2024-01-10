#ifndef __EV_COMMAND_POOL_CPP__
#define __EV_COMMAND_POOL_CPP__

#include "ev_command_pool.h"

using namespace EasyVulkan;

/** Public Methods **/

CommandPool::CommandPool(Device *device, VkQueueFlags queue_flag) : DeviceBase(device) {
    _queue_family_index = _device->get_queue_family_index(queue_flag);
    create();
}

CommandPool::~CommandPool() {
    destroy();
}

VkResult CommandPool::create() {
    if(_command_pool != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }

    VkCommandPoolCreateInfo command_pool_ci{};
    command_pool_ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_ci.pNext = nullptr;
    command_pool_ci.queueFamilyIndex = _device->get_queue_family_index(_queue_flag);
    command_pool_ci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    return vkCreateCommandPool(_device->device(), &command_pool_ci, nullptr, &_command_pool);
}

void CommandPool::destroy() {
    if(_command_pool !=VK_NULL_HANDLE) {
        vkDestroyCommandPool(_device->device(), _command_pool, nullptr);
        _command_pool = VK_NULL_HANDLE;
    }
}

VkCommandPool CommandPool::command_pool() {
    return _command_pool;
}

#endif