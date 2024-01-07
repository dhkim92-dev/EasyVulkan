#ifndef __EV_MEMORY_ALLOCATE_INFO_CPP__
#define __EV_MEMORY_ALLOCATE_INFO_CPP__

#include "builder/ev_memory_ai.h"

namespace EasyVulkan 
{
    namespace Builder {


        MemoryAllocateInfo* MemoryAllocateInfo::next(void *value) {
            _next = value;

            return this;
        }


        MemoryAllocateInfo* MemoryAllocateInfo::memory_type_index(uint32_t index) {
            _memory_type_index = index;

            return this;
        }

        MemoryAllocateInfo* MemoryAllocateInfo::size(VkDeviceSize value) {
            _size = value;
            
            return this;
        }

        VkMemoryAllocateInfo MemoryAllocateInfo::build() {
            VkMemoryAllocateInfo info{};
            info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            info.pNext = _next;
            info.memoryTypeIndex = _memory_type_index;
            info.allocationSize = _size;

            return info;
        }
    }
}

#endif