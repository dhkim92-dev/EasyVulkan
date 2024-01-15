#ifndef __EV_MEMORY_FACTORY_H__
#define __EV_MEMORY_FACTORY_H__

#include <vulkan/vulkan.h>
#include <cassert>
#include "ev_buffer.h"
#include "ev_device.h"
#include "ev_memory.h"
#include "initializer/ev_memory_ai.h"

namespace EasyVulkan {
    namespace Factory {

        class MemoryFactory : DeviceBase {
            
            public:

            explicit MemoryFactory(Device *device);

            Memory* create_buffer_memory(Buffer *buffer, VkMemoryPropertyFlags flags, VkDeviceSize size);
        };
    }
}

#endif