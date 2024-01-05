#ifndef __EV_TEST_UTILITY_HPP__
#define __EV_TEST_UTILITY_HPP__

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "easy_vulkan.h"

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN 1
#include "GLFW/glfw3.h"
#endif

using namespace std;
using namespace EasyVulkan;

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
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_KHRONOS_profiles"
    };

    Instance *instance = new Instance(instance_extensions, validation_layers);
    instance->set_debug(true);
    EasyVulkan::Info::ApplicationInfo* app_info = new EasyVulkan::Info::ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));
    
    instance->create(app_info);
    delete app_info;
    return instance;
}

Device* create_ev_device(Instance *instance, vector<const char*> enabled_extensions) 
{
    assert(instance != nullptr);
    cout << "instance id : " << instance << endl;
    Device* device = new Device(instance, 0);
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
        "VK_LAYER_KHRONOS_profiles"
    };

    for(auto name : instance_extensions) {
        cout << name << endl;
    }
    Instance *instance = new Instance(instance_extensions, validation_layers);
    cout << "instance id : " << instance << endl;
    instance->set_debug(true);
    EasyVulkan::Info::ApplicationInfo* app_info = new EasyVulkan::Info::ApplicationInfo();
    app_info->api_version(VK_API_VERSION_1_3)
    ->app_name("easy-vulkan-test")
    ->engine_name("easy-vulkan-test")
    ->app_version(VK_MAKE_VERSION(1, 0, 0))
    ->engine_version(VK_MAKE_VERSION(1, 0, 0));

    instance->create(app_info);
    CHECK_VK_RESULT(glfwCreateWindowSurface(instance->instance(), window, nullptr, surface));
    delete app_info;
    return instance;
}

GLFWwindow* create_glfw_window() {
    GLFWwindow *window;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(1024, 576, "Vulkan", nullptr, nullptr);
    if(!window){
		throw std::runtime_error("glfwWindowCreate failed error.\n");
    }

    cout << "GLFWwindow created." << endl;

    return window;
}


#endif