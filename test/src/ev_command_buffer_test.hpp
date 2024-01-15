#ifndef __EV_COMMAND_BUFFER_TEST_HPP__
#define __EV_COMMAND_BUFFER_TEST_HPP__

#include "test_utility.hpp"

extern CommandPool *command_pool;

TEST(COMMAND_BUFFER_TEST, end_command_buffer) {
    CommandBuffer *command_buffer = nullptr;
    command_buffer = new CommandBuffer(device, command_pool);
    VkResult result = command_buffer->begin();
    EXPECT_EQ(result, VK_SUCCESS);
    EXPECT_NO_THROW(
        command_buffer->end();
    );

    delete command_buffer;
}

TEST(COMMAND_BUFFER_TEST, begin_command_buffer) {
    CommandBuffer *command_buffer = nullptr;
    command_buffer = new CommandBuffer(device, command_pool);
    VkResult result = command_buffer->begin();
    EXPECT_EQ(result, VK_SUCCESS);

    delete command_buffer;
}

TEST(COMMAND_BUFFER_TEST, create_command_buffer) {
    CommandBuffer *command_buffer = nullptr;
    command_buffer = new CommandBuffer(device, command_pool);
    EXPECT_NE(command_buffer, nullptr);

    delete command_buffer;
}

#endif