#ifndef __EV_QUEUE_SI_H__
#define __EV_QUEUE_SI_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <algorithm>

using namespace std;

namespace EasyVulkan {
    namespace Initializer {
        class SubmitInfo {

            vector<VkSemaphore> _wait_semaphores;

            vector<VkSemaphore> _signal_semaphores;

            vector<VkCommandBuffer> _command_buffers;

            VkPipelineStageFlags _wait_dst_stage_mask = VK_PIPELINE_STAGE_NONE;

            void *_next = nullptr;

            public : 

            SubmitInfo* wait_dst_stage(VkPipelineStageFlags value);

            SubmitInfo* wait_semaphores(vector<VkSemaphore> value);

            SubmitInfo* signal_semaphores(vector<VkSemaphore> value);

            SubmitInfo* next(void *value);

            VkSubmitInfo build();
        };
    }
}

#endif