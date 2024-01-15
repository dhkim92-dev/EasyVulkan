#ifndef __EV_BUFFER_H__
#define __EV_BUFFER_H__

#include <vulkan/vulkan.h>
#include "ev_device.h"
#include "initializer/ev_buffer_ci.h"
#include "ev_memory.h"
#include "ev_utility.h"

using namespace EasyVulkan::Initializer;

namespace EasyVulkan {

    class Buffer : DeviceBase {

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

        explicit Buffer(Device *device, BufferCreateInfo* buffer_ci);

        ~Buffer();

        VkResult create_buffer(BufferCreateInfo* buffer_ci);

        void copy(void *src, VkDeviceSize size); 

        void dump(void *dst, VkDeviceSize size);

        VkResult map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        void unmap();

        VkResult bind(Memory *memory, VkDeviceSize offset = 0);

        VkResult flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        VkResult invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        void destroy();

        //getter

        VkBuffer buffer();

        VkBuffer& buffer_alias();

        VkBuffer* buffer_ptr();

        Memory *memory();

        VkDeviceSize offset();

        VkDeviceSize size();

        VkDeviceSize alignment();

        VkBufferUsageFlags usage();

        VkMemoryRequirements memory_requirements();
    };
}


#endif