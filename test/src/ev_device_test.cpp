#ifndef __EV_DEVICE_TEST_CPP__
#define __EV_DEVICE_TEST_CPP__

#include <gtest/gtest.h>
#include "easy_vulkan.h"
#include <iostream>

using namespace EasyVulkan;

Instance* create_instance()
{
    vector<const char *> instance_extensions = {
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

    vector<const char *> validation_layers = {
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_KHRONOS_profiles"
    };

    LOGD("EasyVulkan::Instance created.");

    Instance *instance = new Instance(instance_extensions, validation_layers);
    instance->set_debug(true);
    Initializer::ApplicationInfo* app_info = new Initializer::ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));
    instance->create(app_info);

    delete app_info;
    return instance;
}


TEST(EasyVulkanDeviceTest, device_create_test) {
    Instance *instance = create_instance();
    Device *device = new Device(instance, 0);
    EXPECT_NE(device->physical_device(), (VkPhysicalDevice)(VK_NULL_HANDLE));
    delete device;
    delete instance;
}

TEST(EasyVulkanDeviceTest, logical_device_create_test) {
    Instance *instance = create_instance();
    Device *device = new Device(instance, 0);
    VkPhysicalDeviceFeatures features{};
    device->create_logical_device(
        features, {}
    );

    EXPECT_NE(device->device(), (VkDevice)(VK_NULL_HANDLE));
    delete device;
    delete instance;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    return ret;
}

#endif