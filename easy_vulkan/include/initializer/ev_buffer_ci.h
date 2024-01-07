#ifndef __EV_BUFFER_CREATE_INFO_H__
#define __EV_BUFFER_CREATE_INFO_H__

#include <vulkan/vulkan.h>
#include <cassert>
#include "ev_utility.h"

namespace EasyVulkan {
    namespace Initializer {

        class BufferCreateInfo {

            VkBufferCreateFlags _flags = VK_FLAGS_NONE;

            void *_next = nullptr;

            uint32_t *_queue_family_indices = nullptr;

            uint32_t _queue_family_index_count = 0;

            VkDeviceSize _size = 0;

            VkBufferUsageFlags _usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

            VkSharingMode _sharing_mode = VK_SHARING_MODE_EXCLUSIVE;

            public : 

            BufferCreateInfo* flags(VkBufferCreateFlags value);

            BufferCreateInfo* next(void *value);

            BufferCreateInfo* queue_family_indices(uint32_t *value);

            BufferCreateInfo* queue_family_index_count(uint32_t value);

            BufferCreateInfo* usage(VkBufferUsageFlags value);

            BufferCreateInfo* sharing_mode(VkSharingMode value);

            BufferCreateInfo* size(VkDeviceSize value);

            VkBufferCreateInfo build();
        };
    }
}

#endif