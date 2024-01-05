#ifndef __EV_SWAPCHAIN_H__
#define __EV_SWAPCHAIN_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <cassert>
#include "ev_instance.h"
#include "ev_device.h"
#include "ev_utility.h"

using namespace std;

namespace EasyVulkan {

    typedef struct _SwapchainBuffer {

        VkImage image;

        VkImageView image_view;

    } SwapchainBuffer;
        
    class Swapchain {
    
        Instance* _instance;

        Device* _device;

        VkFormat _color_format;
        
        VkColorSpaceKHR _color_space;

        VkSurfaceKHR _surface = VK_NULL_HANDLE;

        VkSwapchainKHR _swapchain = VK_NULL_HANDLE;

        uint32_t _image_count;

        uint32_t queue_index = UINT32_MAX;

        vector<VkImage> _images;

        vector<SwapchainBuffer> _buffers;

        void get_surface_capabilities(VkSurfaceCapabilitiesKHR *capabilities);

        void get_present_modes(uint32_t *count, VkPresentModeKHR* present_modes);

        void setup_swapchain_extent(VkSurfaceCapabilitiesKHR* capabilities, VkExtent2D* extent, uint32_t* width, uint32_t* height);

        void setup_present_mode(VkPresentModeKHR *present_mode, VkPresentModeKHR *present_modes, uint32_t count, bool vsync = false);

        public :
        
        /**
         * @brief Swapchain constructor
         * @param _instance {Instance *}
         * @param _device {Device *}
        */
        explicit Swapchain(Instance* instance, Device* device, VkSurfaceKHR surface);
        
        ~Swapchain();

        void setup_screen(uint32_t *width, uint32_t *height, bool vsync = false, bool fullscreen = false);

        Instance* instance();

        Device* device();

        VkFormat color_format();

        VkColorSpaceKHR color_space();

        VkSurfaceKHR surface();

        VkSwapchainKHR swapchain();
        
        vector<VkImage> images();

        vector<SwapchainBuffer> swapchain_buffers();

        VkResult acquire_next_image(VkSemaphore present, uint32_t *image_index);

        VkResult queue_present(VkQueue queue, uint32_t image_index, VkSemaphore waitSemaphore);

        void destroy();
    };
}

#endif