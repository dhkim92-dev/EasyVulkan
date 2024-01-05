#ifndef __EV_SWAPCHAIN_CPP__
#define __EV_SWAPCHAIN_CPP__

#include "ev_swapchain.h"

using namespace EasyVulkan;

Swapchain::Swapchain(Instance *inst, Device *dev, VkSurfaceKHR surf) {
    _instance = inst;
    _device = dev;
    _surface = surf;
}

Swapchain::~Swapchain() {
    destroy();
}

/*--------- Private Methods ----------*/
void Swapchain::get_surface_capabilities(VkSurfaceCapabilitiesKHR *capabilities) {
    CHECK_VK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device->physical_device(),_surface, capabilities));
}

void Swapchain::get_present_modes(uint32_t *count, VkPresentModeKHR *present_modes) {
    CHECK_VK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(_device->physical_device(), _surface, count, present_modes));
}

void Swapchain::setup_swapchain_extent(VkSurfaceCapabilitiesKHR* capabilities, VkExtent2D* extent, uint32_t* width, uint32_t* height) {
    if(capabilities->currentExtent.width == (uint32_t)-1) {
        extent->width = *width;
        extent->height= *height;
    } else {
        *extent = capabilities->currentExtent;
        *width = capabilities->currentExtent.width;
        *height = capabilities->currentExtent.height;
    }
}

void Swapchain::setup_present_mode(VkPresentModeKHR *present_mode, VkPresentModeKHR *present_modes, uint32_t count, bool vsync) {
    *present_mode = VK_PRESENT_MODE_FIFO_KHR;

    if(!vsync) {
        for(size_t i = 0 ; i < count ; i++) {
            if(present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
                *present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
            }

            if(present_modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                *present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
            }
        }
    }
}

/*--------- Public Methods -----------*/
void Swapchain::setup_screen(uint32_t *width, uint32_t *height, bool vsync, bool fullscreen) {
    VkSwapchainKHR old_swapchain = _swapchain;
    VkSurfaceCapabilitiesKHR surface_capabilities;
    get_surface_capabilities(&surface_capabilities);

    uint32_t present_mode_count;
    get_present_modes(&present_mode_count, nullptr);
    assert(present_mode_count > 0);
    vector<VkPresentModeKHR> present_modes(present_mode_count);
    get_present_modes(&present_mode_count, present_modes.data());
    VkExtent2D swapchain_extent = {};
    setup_swapchain_extent(&surface_capabilities, &swapchain_extent, width, height);
    VkPresentModeKHR present_mode;
    setup_present_mode(&present_mode, present_modes.data(), present_mode_count, vsync);

    uint32_t desired_swapchain_image_count = surface_capabilities.minImageCount + 1;
    if((surface_capabilities.maxImageCount > 0) && (desired_swapchain_image_count > surface_capabilities.maxImageCount)) {
        desired_swapchain_image_count = surface_capabilities.maxImageCount;    
    }
    
    VkSurfaceTransformFlagsKHR pre_transform = (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) 
    ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR : surface_capabilities.currentTransform;

    VkCompositeAlphaFlagBitsKHR composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    vector<VkCompositeAlphaFlagBitsKHR> composite_alpha_flags = {VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR, VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR, VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR};

    for(auto& composite_alpha_flag : composite_alpha_flags) {
        if(surface_capabilities.supportedCompositeAlpha & composite_alpha_flag) {
            composite_alpha = composite_alpha_flag;
            break;
        }
    }

    VkSwapchainCreateInfoKHR swapchain_ci = {};
    swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.surface = _surface;
    swapchain_ci.minImageCount = desired_swapchain_image_count;
    swapchain_ci.imageFormat = _color_format;
    swapchain_ci.imageColorSpace = _color_space;
    swapchain_ci.imageExtent = {swapchain_extent.width, swapchain_extent.height};
    swapchain_ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_ci.preTransform = (VkSurfaceTransformFlagBitsKHR)pre_transform;
    swapchain_ci.imageArrayLayers = 1;
    swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_ci.queueFamilyIndexCount = 0;
    swapchain_ci.presentMode = present_mode;
    swapchain_ci.oldSwapchain = old_swapchain;
    swapchain_ci.clipped = VK_TRUE;
    swapchain_ci.compositeAlpha = composite_alpha;

    if(surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
        swapchain_ci.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    }

    if(surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
        swapchain_ci.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    CHECK_VK_RESULT(vkCreateSwapchainKHR(_device->device(), &swapchain_ci, nullptr, &_swapchain));
    _images.resize(_image_count);
    CHECK_VK_RESULT(vkGetSwapchainImagesKHR(_device->device(), _swapchain, &_image_count, _images.data()));
    _buffers.resize(_image_count);

    for(uint32_t i = 0 ; i < _image_count ; i++) {
        VkImageViewCreateInfo image_view_ci = {};
        image_view_ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_ci.pNext = NULL;
        image_view_ci.format = _color_format;
        image_view_ci.components = {
            VK_COMPONENT_SWIZZLE_R, 
            VK_COMPONENT_SWIZZLE_G,
            VK_COMPONENT_SWIZZLE_B,
            VK_COMPONENT_SWIZZLE_A
        };
        image_view_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_ci.subresourceRange.baseMipLevel = 0;
        image_view_ci.subresourceRange.levelCount = 1;
        image_view_ci.subresourceRange.baseArrayLayer = 0;
        image_view_ci.subresourceRange.layerCount = 1;
        image_view_ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_ci.flags = 0;
        _buffers[i].image = _images[i];
        CHECK_VK_RESULT(vkCreateImageView(_device->device(), &image_view_ci, nullptr, &_buffers[i].image_view));
    }
}

Instance* Swapchain::instance() {
    return _instance;
}

Device* Swapchain::device() {
    return _device;
}

VkFormat Swapchain::color_format() {
    return _color_format;
}

VkColorSpaceKHR Swapchain::color_space() {
    return _color_space;
}

VkSurfaceKHR Swapchain::surface() {
    return _surface;
}

VkSwapchainKHR Swapchain::swapchain() {
    return _swapchain;
}

vector<VkImage> Swapchain::images() {
    return _images;
}

vector<SwapchainBuffer> Swapchain::swapchain_buffers() {
    return _buffers;
}

VkResult Swapchain::acquire_next_image(VkSemaphore present, uint32_t *image_index) {
    return vkAcquireNextImageKHR(_device->device(), _swapchain, UINT64_MAX, present, (VkFence)nullptr, image_index);
}

VkResult Swapchain::queue_present(VkQueue queue, uint32_t image_index, VkSemaphore wait_semaphore) {
    VkPresentInfoKHR present_info = {};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.pNext = NULL;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &_swapchain;
    present_info.pImageIndices = &image_index;

    if(wait_semaphore != VK_NULL_HANDLE) {
        present_info.pWaitSemaphores = &wait_semaphore;
        present_info.waitSemaphoreCount = 1;
    }

    return vkQueuePresentKHR(queue, &present_info);
}

void Swapchain::destroy() {
    if(_swapchain != VK_NULL_HANDLE) {
        for(uint32_t i = 0 ; i < _image_count ; i++) {
            vkDestroyImageView(_device->device(), _buffers[i].image_view, nullptr);
        }
        _buffers.clear();
    }

    if(_surface != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(_device->device(), _swapchain, nullptr);
        vkDestroySurfaceKHR(_instance->instance(), _surface, nullptr);
    }

    _surface = VK_NULL_HANDLE;
    _swapchain = VK_NULL_HANDLE;
}

#endif