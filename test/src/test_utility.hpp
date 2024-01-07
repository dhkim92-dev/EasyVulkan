#ifndef __EV_TEST_UTILITY_HPP__
#define __EV_TEST_UTILITY_HPP__

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <gtest/gtest.h>
#include "easy_vulkan.h"

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN 1
#include "GLFW/glfw3.h"
#endif

using namespace std;
using namespace EasyVulkan;
using namespace EasyVulkan::Initializer;
using namespace EasyVulkan::Factory;

Instance* create_ev_instance() 
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
        "VK_LAYER_KHRONOS_profiles"
    };

    Instance *instance = new Instance(instance_extensions, validation_layers);
    instance->set_debug(true);
    ApplicationInfo* app_info = new ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));
    
    instance->create(app_info);
    delete app_info;
    return instance;
}

Device* create_ev_device(Instance *instance, vector<const char*> enabled_extensions, uint32_t gpu_id) 
{
    assert(instance != nullptr);
    cout << "instance id : " << instance << endl;
    Device* device = new Device(instance, gpu_id);
    VkPhysicalDeviceFeatures features{};
    device->create_logical_device(
        features, 
        {}, 
        VK_QUEUE_GRAPHICS_BIT, 
        nullptr, 
        true);
    return device;
} 

Instance* create_instance_with_surface(GLFWwindow *window, VkSurfaceKHR *surface) {
    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);
    vector<const char*> instance_extensions(extensions, extensions + count);
    vector<const char*> validation_layers = {
        "VK_LAYER_KHRONOS_validation",
    };

    for(auto name : instance_extensions) {
        LOGI("Instance extension requested : %s", name);
    }
    Instance *instance = new Instance(instance_extensions, validation_layers);
    cout << "instance id : " << instance << endl;
    instance->set_debug(true);
    ApplicationInfo* app_info = new ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));

    instance->create(app_info);
    LOGI("Instance created.");
    CHECK_VK_RESULT(glfwCreateWindowSurface(instance->instance(), window, nullptr, surface));
    LOGI("Surface created.");
    delete app_info;
    return instance;
}

GLFWwindow* create_glfw_window() {
    GLFWwindow *window;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(1024, 576, "Vulkan", nullptr, nullptr);
    if(!window){
		throw std::runtime_error("glfwWindowCreate failed error.\n");
    }

    cout << "GLFWwindow created." << endl;

    return window;
}


#define NONE_SURFACE_TEST_MAIN()  \
int main(int argc, char *argv[])    \
{   \
    instance = create_ev_instance();    \
    device = create_ev_device(instance, {}, 0); \
    testing::InitGoogleTest(&argc, argv);   \
    int ret = RUN_ALL_TESTS();              \
    delete device;                          \
    delete instance;                        \      
    return ret;                             \
}   



#endif