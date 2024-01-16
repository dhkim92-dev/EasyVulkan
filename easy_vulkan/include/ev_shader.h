#ifndef __EV_SHADER_H__
#define __EV_SHADER_H__

#include <vulkan/vulkan.h>
#include <string>
#include "ev_device.h"

namespace EasyVulkan {

    class Shader : public DeviceBase {
        
        VkShaderModule _module = VK_NULL_HANDLE;

        VkShaderStageFlagBits _stage;

        string _entrypoint = "main";

        public : 

        explicit Shader(Device *device, VkShaderStageFlagBits stage);

        ~Shader();

        VkResult create(VkShaderModuleCreateInfo *info);

        VkShaderModule module() const;
        
        VkShaderModule* module_ptr();

        VkShaderStageFlagBits stage() const;

        string entrypoint() const;

        void set_entrypoint(string value);

        void destroy();
    };
}

#endif