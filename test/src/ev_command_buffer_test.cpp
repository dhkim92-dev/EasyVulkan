#ifndef __EV_COMMAND_BUFFER_TEST_CPP__
#define __EV_COMMAND_BUFFER_TEST_CPP__

#include "test_utility.hpp"

Instance *instance = nullptr;
Device *device = nullptr;
CommandPool *command_pool = nullptr;

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

COMMAND_POOL_TEST_MAIN()

#endif