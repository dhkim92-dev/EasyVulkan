#ifndef __EV_SWAPCHAIN_TEST_CPP__
#define __EV_SWAPCHAIN_TEST_CPP__

#include <gtest/gtest.h>
#include "easy_vulkan.h"
#include "test_utility.hpp"

using namespace EasyVulkan;

Instance *instance = nullptr;
GLFWwindow *window = nullptr;
VkSurfaceKHR surface = VK_NULL_HANDLE;

TEST(EasyVulkanSwapchainTest, create_swapchain) {
    Device *device = new Device(instance, 1);
    VkPhysicalDeviceFeatures features{};
    device->create_logical_device(features, {}, VK_QUEUE_GRAPHICS_BIT, nullptr, true);
    EXPECT_NE(device, nullptr);

    Swapchain *swapchain = new Swapchain(instance, device, surface);
    uint32_t width = 1024;
    uint32_t height = 564;
    swapchain->setup_screen(&width, &height, false, false);
    //delete swapchain;
    int t = 1000;

    delete swapchain;
    delete device;
}

int main(int argc, char *argv[])
{    
    glfwInit();
    window = create_glfw_window();
    instance = create_instance_with_surface(window, &surface);
    assert(surface != VK_NULL_HANDLE);
    testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    glfwDestroyWindow(window);
    glfwTerminate();
    return ret;
}

#endif