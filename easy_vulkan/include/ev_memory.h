#ifndef __EV_MEMORY_H__
#define __EV_MEMORY_H__

#include <vulkan/vulkan.h>
#include "initializer/ev_memory_ai.h"
#include "ev_device.h"
#include "ev_utility.h"

using namespace EasyVulkan::Initializer;

namespace EasyVulkan 
{

    class Memory {
        
        Device *_device = nullptr;

        VkDeviceMemory _memory = VK_NULL_HANDLE;

        VkDeviceSize _size = 0 ;

        VkMemoryPropertyFlags _flags;

        uint32_t _memory_type_bit;

        public :
        
        explicit Memory(Device *device);

        ~Memory();

        void release();

        VkResult allocate(MemoryAllocateInfo *info);

        Device* device();

        VkDeviceMemory memory();

        VkDeviceSize size();

        VkMemoryPropertyFlags flags();

        uint32_t type();
    };
}

#endif