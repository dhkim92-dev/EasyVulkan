#ifndef __EV_INSTANCE_TEST_CPP__
#define __EV_INSTANCE_TEST_CPP__

#include <gtest/gtest.h>
#include "easy_vulkan.h"

using namespace EasyVulkan;

VkInstance create_instance_success()
{
    vector<char *> instance_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef __APPLE__
        "VK_EXT_metal_surface",
#endif
#ifdef __LINUX__
        "VK_KHR_wayland_surface",
        "VK_KHR_xcb_surface",
        "VK_KHR_xlib_surface"
#endif
    };

    vector<char *> validation_layers = {
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_KHRONOS_profiles"
    };

    LOGD("EasyVulkan::Instance created.");

    Instance instance(instance_extensions, validation_layers);
    EasyVulkan::Info::ApplicationInfo* app_info = new EasyVulkan::Info::ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));

    instance.create(app_info);
    delete app_info;

    return instance.instance();
}

TEST(EasyVulkanInstanceTest, InstanceCreate) {
    EXPECT_NE(create_instance_success(), (VkInstance)NULL);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif