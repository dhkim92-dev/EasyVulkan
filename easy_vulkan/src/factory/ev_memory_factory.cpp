#ifndef __EV_MEMORY_FACTORY_CPP__
#define __EV_MEMORY_FACTORY_CPP__

#include "factory/ev_memory_factory.h"

namespace EasyVulkan {

    namespace Factory {

        MemoryFactory::MemoryFactory(Device *_device) : device(_device) {
            assert(_device != nullptr);
        }

        Memory* MemoryFactory::create_buffer_memory(Buffer *buffer, VkMemoryPropertyFlags flags, VkDeviceSize size) {
            assert(buffer != nullptr);
            auto requirements = buffer->memory_requirements();
            VkBool32 found = VK_FALSE;
            uint32_t memory_type_index = device->get_memory_type(requirements.memoryTypeBits, flags, &found);

            VkMemoryAllocateFlagsInfoKHR alloc_flags_info{};
            auto memory_ai = Builder::MemoryAllocateInfo();
            memory_ai.flags = flags;
            memory_ai.size(requirements.size)
                    ->memory_type_index(memory_type_index);

            if(buffer->usage() & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
                alloc_flags_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
                alloc_flags_info.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
                memory_ai.next(&alloc_flags_info);           
            }
            
            Memory *memory = new Memory(device);
            memory->allocate(&memory_ai);

            return memory;
        }
    }
}

#endif