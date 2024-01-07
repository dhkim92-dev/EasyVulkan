#ifndef __EV_BUFFER_FACTORY_CPP__
#define __EV_BUFFER_FACTORY_CPP__

#include "factory/ev_buffer_factory.h"

namespace EasyVulkan {
    namespace Factory {

        BufferFactory::BufferFactory(Device *device) : device(device){
            assert(device != nullptr);
        }

        Buffer* BufferFactory::create_buffer(VkBufferUsageFlags usage, VkDeviceSize size) {
            auto ci = Builder::BufferCreateInfo();
            ci.usage(usage);
            Buffer *buffer = new Buffer(device);
            buffer->create_buffer(&ci);
            return buffer;
        }
    }
}

#endif