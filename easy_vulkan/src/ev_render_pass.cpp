#ifndef __EV_RENDER_PASS_CPP__
#define __EV_RENDER_PASS_CPP__

#include "ev_render_pass.h"

using namespace EasyVulkan;

RenderPass::RenderPass(Device *device) : DeviceBase(device) {

}

RenderPass::~RenderPass() {
    destroy();
}

VkResult RenderPass::create(VkRenderPassCreateInfo *info) {
    if(_render_pass != VK_NULL_HANDLE) {
        LOGE("VkRenderPass is already created.");
        return VK_SUCCESS;
    }

    return vkCreateRenderPass(_device->device(), info, nullptr, &_render_pass);
}

VkRenderPass RenderPass::render_pass() const {
    return _render_pass;
}

VkRenderPass* RenderPass::render_pass_ptr() {
    return &_render_pass;
}

void RenderPass::destroy() {
    if(_render_pass == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyRenderPass(_device->device(), _render_pass, nullptr);
    _render_pass = VK_NULL_HANDLE;
}

#endif