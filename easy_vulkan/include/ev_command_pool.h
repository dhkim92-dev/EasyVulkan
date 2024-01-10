#ifndef __EV_COMMAND_POOL_H__
#define __EV_COMMAND_POOL_H__

#include <vulkan/vulkan.h>
#include "base/ev_device_base.h"
#include "ev_device.h"

using namespace std;

namespace EasyVulkan {

    class CommandPool : DeviceBase {

        VkCommandPool _command_pool = VK_NULL_HANDLE;

        VkQueueFlags _queue_flag = VK_QUEUE_GRAPHICS_BIT;

        uint32_t _queue_family_index = 0;

        public : 

        explicit CommandPool(Device *device, VkQueueFlags queue_flag);

        ~CommandPool();

        VkResult create();

        void destroy();

        VkCommandPool command_pool();
    };
}

#endif