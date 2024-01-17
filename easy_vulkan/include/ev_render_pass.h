#ifndef __EV_RENDER_PASS_H__
#define __EV_RENDER_PASS_H__

#include <vulkan/vulkan.h>
#include "ev_device.h"

namespace EasyVulkan {
    class RenderPass : public DeviceBase {

        VkRenderPass _render_pass = VK_NULL_HANDLE;

        public :

        RenderPass(Device *device);

        ~RenderPass();

        VkResult create(VkRenderPassCreateInfo *info);

        VkRenderPass render_pass() const;

        VkRenderPass* render_pass_ptr();

        void destroy();
    };
}

#endif