#ifndef __EV_SHADER_CPP__
#define __EV_SHADER_CPP__

#include "ev_shader.h"

using namespace EasyVulkan;

Shader::Shader(Device *device, VkShaderStageFlagBits stage) : DeviceBase(device), _stage(stage) {

}

Shader::~Shader() {
    destroy();
}

VkResult Shader::create(VkShaderModuleCreateInfo *info) {
    if(_module != VK_NULL_HANDLE) {
        LOGE("Shader module already exists.");
        return VK_SUCCESS;
    }

    return vkCreateShaderModule(_device->device(), info, nullptr, &_module);
}

VkShaderModule Shader::module() const {
    return _module;
}

VkShaderModule* Shader::module_ptr() {
    return &_module;
}

VkShaderStageFlagBits Shader::stage() const {
    return _stage;
}

void Shader::destroy() {
    if(_module == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyShaderModule(_device->device(), _module, nullptr);
    _module = VK_NULL_HANDLE;
}

#endif