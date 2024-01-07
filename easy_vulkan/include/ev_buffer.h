#ifndef __EV_BUFFER_H__
#define __EV_BUFFER_H__

#include <vulkan/vulkan.h>
#include "builder/ev_buffer_ci.h"
#include "ev_memory.h"
#include "ev_device.h"
#include "ev_utility.h"

namespace EasyVulkan {

    class Buffer {
        Device *_device = nullptr;

        VkBuffer _buffer = VK_NULL_HANDLE;

        Memory *_memory = nullptr;

        VkDeviceSize _size = 0;

        VkDeviceSize _offset = 0;

        VkDeviceSize _alignment = 0;

        VkBufferUsageFlags _usage;

        VkMemoryRequirements _memory_requirements;

        public:

        void* mapped = nullptr;

        explicit Buffer(Device *device);

        explicit Buffer(Device *device, Builder::BufferCreateInfo* buffer_ci);

        ~Buffer();

        VkResult create_buffer(Builder::BufferCreateInfo* buffer_ci);

        void copy_to(void *data, VkDeviceSize size); 

        void copy_from(void *data, VkDeviceSize size);

        VkResult map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        void unmap();

        VkResult bind(Memory *memory, VkDeviceSize offset = 0);

        VkResult flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        VkResult invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        void destroy();

        //getter

        VkBuffer buffer();

        Memory *memory();

        VkDeviceSize offset();

        VkDeviceSize size();

        VkDeviceSize alignment();

        VkBufferUsageFlags usage();

        VkMemoryRequirements memory_requirements();
    };
}


#endif