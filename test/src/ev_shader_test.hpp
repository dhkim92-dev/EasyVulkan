#ifndef __EV_SHADER_HPP__
#define __EV_SHADER_HPP__

#include "test_utility.hpp"

using namespace EasyVulkan;

extern Instance* instance;
extern Device* device;

TEST(EV_SHADER_TEST, create_shader) {
    size_t size = 0;
    char *vertex_shader_code = Utility::load_shader_code("../../shaders/test/test.vert.spv", &size);

    EXPECT_GT(size, 0);

    Shader vertex_shader(device, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderModuleCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = size;
    info.pCode = (uint32_t *)vertex_shader_code;

    VkResult result = vertex_shader.create(&info);

    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NE(vertex_shader.module(), VK_NULL_HANDLE);
}

#endif