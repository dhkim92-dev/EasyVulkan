#ifndef __EV_BUFFER_FACTORY_CPP__
#define __EV_BUFFER_FACTORY_CPP__

#include "factory/ev_buffer_factory.h"

using namespace EasyVulkan;
using namespace EasyVulkan::Initializer;
using namespace EasyVulkan::Factory;

BufferFactory::BufferFactory(Device *device) : DeviceBase(device) {
}

Buffer* BufferFactory::create_buffer(VkBufferUsageFlags usage, VkDeviceSize size) {
    auto ci = BufferCreateInfo();
    ci.usage(usage)
        ->size(size);
    Buffer *buffer = new Buffer(_device);
    buffer->create_buffer(&ci);
    return buffer;
}

#endif