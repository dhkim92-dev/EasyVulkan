#ifndef __EV_MEMORY_ALLOCATE_INFO_H__
#define __EV_MEMORY_ALLOCATE_INFO_H__

#include <vulkan/vulkan.h>
#include "ev_utility.h"

using namespace std;

namespace EasyVulkan {
    namespace Initializer {

        class MemoryAllocateInfo {
            
            void* _next = nullptr;

            uint32_t _memory_type_index = 0;

            VkDeviceSize _size = 0;

            public: 

            VkMemoryPropertyFlags flags;

            MemoryAllocateInfo* next(void *value);
            
            MemoryAllocateInfo* memory_type_index(uint32_t value);

            MemoryAllocateInfo* size(VkDeviceSize value);

            VkMemoryAllocateInfo build();
        };
    }
}

#endif