#ifndef __EV_QUEUE_CI_H__
#define __EV_QUEUE_CI_H__

#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include "ev_utility.h"

using namespace std;

namespace EasyVulkan {
    namespace Info {

        class QueueCreateInfo {

            VkDeviceQueueCreateFlags _flags = VK_FLAGS_NONE;

            void* _next = VK_NULL_HANDLE;

            uint32_t _count = 0;

            float _priorities = 1.0f;

            uint32_t _index = 0;

            public:

            QueueCreateInfo* flags(VkDeviceQueueCreateFlags value);

            QueueCreateInfo* next(void *value);

            QueueCreateInfo* queue_count(uint32_t value);

            QueueCreateInfo* queue_priorities(float value);

            QueueCreateInfo* queue_index(uint32_t value);
            
            VkDeviceQueueCreateInfo build();     
        };
    }
}

#endif