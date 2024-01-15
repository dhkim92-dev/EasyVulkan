#ifndef __COMMAND_BUFFER_POOL_TEST_HPP__
#define __COMMAND_BUFFER_POOL_TEST_HPP__

#include "test_utility.hpp"

extern Instance* instance;
extern Device* device;

TEST(COMMAND_POOL_TEST, create_command_pool_compute) {
    CommandPool *command_pool = new CommandPool(device, VK_QUEUE_COMPUTE_BIT);
    delete command_pool;
}

TEST(COMMAND_POOL_TEST, create_command_pool_graphics) {
    CommandPool *command_pool = new CommandPool(device, VK_QUEUE_GRAPHICS_BIT);

    delete command_pool;
}

#endif