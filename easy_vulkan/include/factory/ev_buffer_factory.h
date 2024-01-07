#ifndef __EV_BUFFER_FACTORY_H__
#define __EV_BUFFER_FACTORY_H__

#include <vulkan/vulkan.h>
#include <cassert>
#include "initializer/ev_buffer_ci.h"
#include "ev_buffer.h"

namespace EasyVulkan {
    namespace Factory {
        class BufferFactory {

            Device *device = nullptr;

            public :

            explicit BufferFactory(Device *device);

            Buffer* create_buffer(VkBufferUsageFlags usage, VkDeviceSize size);
        };
    }
}

#endif