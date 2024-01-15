#ifndef __EV_IMAGE_TEST_HPP__
#define __EV_IMAGE_TEST_HPP__

#include <vulkan/vulkan.h>
#include "easy_vulkan.h"
#include "test_utility.hpp"

using namespace EasyVulkan;

extern Instance* instance;
extern Device* device;

namespace ImageTest {
    Image* create_image() {
        Image *image = new Image(device);
        VkImageCreateInfo info = Initializer::image_create_info(320, 240, 1);
        info.mipLevels = 1;
        info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        image->create_image(&info);

        return image;
    }

    VkResult create_image_view(Image *image) {
        VkImageViewCreateInfo info = Initializer::image_view_create_info();
        info.format  = VK_FORMAT_R8G8B8A8_SRGB;
        info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        info.subresourceRange.baseArrayLayer = 0;
        info.subresourceRange.baseMipLevel = 0;
        info.subresourceRange.layerCount = 1;
        info.subresourceRange.levelCount = 1;

        return image->create_view(&info);
    }

    VkResult create_sampler(Image *image) {
        VkSamplerCreateInfo info = Initializer::sampler_create_info();
        info.maxLod = 1.0f;
        return image->create_sampler(&info);
    }

    Memory* create_image_memory(Image *image, VkMemoryPropertyFlags flags) {
        MemoryFactory factory(device);
        return factory.create_image_memory(image, flags);
    }
}

TEST(EV_IMAGE_TEST, image_create_test) {
    Image *image = ImageTest::create_image();

    EXPECT_NE(image, nullptr);
    EXPECT_NE(image->image(), VK_NULL_HANDLE);

    delete image;
}

TEST(EV_IMAGE_TEST, image_memory_create_test) {
    Image *image = ImageTest::create_image();
    Memory *memory = ImageTest::create_image_memory(image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    EXPECT_NE(memory, nullptr);
    EXPECT_NE(memory->memory(), VK_NULL_HANDLE);
    
    delete image;
    delete memory;
}

TEST(EV_IMAGE_TEST, image_memory_bind_test) {
    Image *image = ImageTest::create_image();
    Memory *memory = ImageTest::create_image_memory(image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    EXPECT_NE(memory, nullptr);
    EXPECT_NE(memory->memory(), VK_NULL_HANDLE);

    VkResult result = image->bind(memory, 0);

    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NE(image->memory(), nullptr);
    
    delete image;
    delete memory;
}

TEST(EV_IMAGE_TEST, image_view_create_test) {
    Image *image = ImageTest::create_image();
    Memory *memory = ImageTest::create_image_memory(image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    EXPECT_NE(memory, nullptr);
    EXPECT_NE(memory->memory(), VK_NULL_HANDLE);

    VkResult result = image->bind(memory, 0);

    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NE(image->memory(), nullptr);

    result = ImageTest::create_image_view(image);
    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NE(image->view(), VK_NULL_HANDLE);
    
    delete image;
    delete memory;
}

TEST(EV_IMAGE_TEST, image_sampler_create_test) {
    Image *image = ImageTest::create_image();

    EXPECT_NE(image, nullptr);
    EXPECT_NE(image->image(), VK_NULL_HANDLE);

    VkResult result = ImageTest::create_sampler(image);

    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NE(image->sampler(), VK_NULL_HANDLE);

    delete image;

}

#endif