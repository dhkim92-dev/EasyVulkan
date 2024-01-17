#ifndef __EV_RENDER_PASS_CPP__
#define __EV_RENDER_PASS_CPP__

#include "initializer/ev_render_pass_ci.h"

using namespace EasyVulkan;

VkRenderPassCreateInfo Initializer::render_pass_create_info() {
    VkRenderPassCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return info;
}

#endif