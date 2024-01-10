#ifndef __EV_QUEUE_H__
#define __EV_QUEUE_H__

#include <vulkan/vulkan.h>
#include "initializer/ev_queue_si.h"
#include "base/ev_device_base.h"
#include "ev_device.h"
#include "ev_fence.h"
#include "ev_command_buffer.h"

using namespace std;
using namespace EasyVulkan::Initializer;

namespace EasyVulkan {
    class CommandQueue : DeviceBase {

        VkQueue _queue = VK_NULL_HANDLE;

        uint32_t _queue_family_index;

        uint32_t _queue_index=0;

        public:
        
        explicit CommandQueue(Device *device, VkQueueFlags flags);

        ~CommandQueue();

        void create();

        VkResult submit(SubmitInfo* submit_info, Fence *fence);

        // TODO present method should be added.

        VkQueue queue();

        VkQueue& queue_alias();

        VkQueue* queue_ptr();

        uint32_t queue_index();

        uint32_t queue_family_index();
    };
}

#endif