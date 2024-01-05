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
    Device *device = create_ev_device(instance, {});
    EXPECT_NE(device, nullptr);
    Swapchain *swapchain = new Swapchain(instance, device, surface);
    uint32_t width = 1024;
    uint32_t height = 564;
    swapchain->setup_screen(&width, &height, false, false);
    delete device;
}

int main(int argc, char *argv[])
{    
    glfwInit();
    window = create_glfw_window();
    cout << "instance id before create surface : " << instance << endl;
    instance = create_instance_with_surface(window, &surface);
    cout << "instance id after create surface : " << instance << endl;
    cout << "surface created." << endl;
    assert(surface != VK_NULL_HANDLE);
    testing::InitGoogleTest(&argc, argv);
    // glfwTerminate();
    // delete instance;
    return RUN_ALL_TESTS();
}

#endif