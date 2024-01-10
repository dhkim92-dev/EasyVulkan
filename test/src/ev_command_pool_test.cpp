#ifndef __COMMAND_BUFFER_POOL_TEST_CPP__
#define __COMMAND_BUFFER_POOL_TEST_CPP__

#include <gtest/gtest.h>
#include "test_utility.hpp"

Instance* instance = nullptr;
Device* device = nullptr;

TEST(COMMAND_POOL_TEST, create_command_pool_compute) {
    CommandPool *command_pool = new CommandPool(device, VK_QUEUE_COMPUTE_BIT);
    delete command_pool;
}

TEST(COMMAND_POOL_TEST, create_command_pool_graphics) {
    CommandPool *command_pool = new CommandPool(device, VK_QUEUE_GRAPHICS_BIT);

    delete command_pool;
}

NONE_SURFACE_TEST_MAIN()

#endif