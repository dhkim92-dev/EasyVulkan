#ifndef __EV_FENCE_H__
#define __EV_FENCE_H__

#include <vulkan/vulkan.h>
#include "base/ev_device_base.h"

namespace EasyVulkan {
    class Fence : DeviceBase {

        VkFence _fence = nullptr;

        public:

        explicit Fence(Device *device);

        ~Fence();

        VkResult create();

        void destroy();

        VkFence fence();
    };
}

#endif