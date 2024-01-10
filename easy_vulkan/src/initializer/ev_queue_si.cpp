#ifndef __EV_QUEUE_SI_CPP__
#define __EV_QUEUE_SI_CPP__

#include "initializer/ev_queue_si.h"

using namespace EasyVulkan::Initializer;

SubmitInfo* SubmitInfo::wait_dst_stage(VkPipelineStageFlags value) {
    _wait_dst_stage_mask = value;

    return this;
}

SubmitInfo* SubmitInfo::signal_semaphores(vector<VkSemaphore> value) {
    if(!value.empty()) {
        _signal_semaphores = value;
    }
    
    return this;
}

SubmitInfo* SubmitInfo::wait_semaphores(vector<VkSemaphore> value) {
    if(!value.empty()) {
        _wait_semaphores = value;
    }

    return this;
}

SubmitInfo* SubmitInfo::next(void* value) {
    _next = value;

    return this;
}

VkSubmitInfo SubmitInfo::build() {
    VkSubmitInfo info {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;
    info.pCommandBuffers = _command_buffers.data();
    info.commandBufferCount = static_cast<uint32_t>(_command_buffers.size());
    info.pWaitDstStageMask = &_wait_dst_stage_mask;

    if(!_signal_semaphores.empty()) {
        info.pSignalSemaphores = _signal_semaphores.data();
        info.signalSemaphoreCount = static_cast<uint32_t>(_signal_semaphores.size());
    }

    if(!_wait_semaphores.empty()) {
        info.pWaitSemaphores = _wait_semaphores.data();
        info.waitSemaphoreCount = static_cast<uint32_t>(_wait_semaphores.size());
    }

    return info;
}

#endif