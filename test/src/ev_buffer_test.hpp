#ifndef __EV_BUFFER_TEST_HPP__
#define __EV_BUFFER_TEST_HPP__

#include "test_utility.hpp"

using namespace std;
using namespace EasyVulkan;
using namespace EasyVulkan::Factory;
using namespace EasyVulkan::Initializer;

extern Instance *instance;
extern Device *device;

TEST(EV_BUFFER_TEST, BUFFR_COPY_AND_DUMP_TEST) {
    auto buffer_factory = BufferFactory(device);

    EasyVulkan::Buffer *buffer1 = nullptr;
    EasyVulkan::Buffer *buffer2 = nullptr;

    buffer1 = buffer_factory.create_buffer(
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 4);
    buffer2 = buffer_factory.create_buffer(
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 4);

    LOGI("buffer1 size : %ld, alignment : %ld\n", buffer1->size(), buffer1->alignment());
    LOGI("buffer2 size : %ld, alignment : %ld\n", buffer2->size(), buffer2->alignment());
    EXPECT_NE(buffer1, nullptr);
    EXPECT_NE(buffer2, nullptr);

    auto memory_factory = MemoryFactory(device);
    Memory *memory = nullptr;
    memory = memory_factory.create_buffer_memory(buffer1, 
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
        buffer1->alignment()*2);
    LOGI("Memory size : %ld", memory->size());
    EXPECT_NE(memory, nullptr);

    buffer1->bind(memory, 0);
    buffer2->bind(memory, buffer1->alignment());

    LOGI("bind complete\n");
    float data1 = 0.3f;
    float data2 = 0.9f;

    buffer1->map(0, 4);
    buffer1->copy(&data1, 4);
    buffer1->unmap();
    buffer2->map(0, 4);
    buffer2->copy(&data2, 4);
    buffer2->unmap();

    float dump1, dump2;

    buffer1->map(0, 4);
    buffer1->dump(&dump1, 4);
    buffer1->unmap();
    buffer2->map(0, 4);
    buffer2->dump(&dump2, 4);
    buffer2->unmap();

    EXPECT_EQ(dump1, data1);
    EXPECT_EQ(dump2, data2);
    
    if(buffer1) {
        delete buffer1;
    }

    if(buffer2) {
        delete buffer2;
    }

    if(memory) {
        delete memory;
    }
}

TEST(EV_BUFFER_TEST, BUFFER_MEMORY_BIND_TEST) {
    auto buffer_factory = BufferFactory(device);
    EasyVulkan::Buffer *buffer = nullptr;
    buffer = buffer_factory.create_buffer(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 4);
    LOGI("buffer size : %ld, alignment : %ld\n", buffer->size(), buffer->alignment());
    EXPECT_NE(buffer, nullptr);
    auto memory_factory = MemoryFactory(device);
    Memory *memory = nullptr;
    memory = memory_factory.create_buffer_memory(buffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, 32);
    EXPECT_NE(memory, nullptr);

    buffer->bind(memory, 0);
    
    if(buffer) {
        delete buffer;
    }

    if(memory) {
        delete memory;
    }

}

TEST(EV_BUFFER_TEST, BUFFER_MEMORY_CREATE_TEST) {
    auto buffer_factory = BufferFactory(device);
    EasyVulkan::Buffer *buffer = nullptr;
    buffer = buffer_factory.create_buffer(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 4);
    LOGI("buffer size : %ld, alignment : %ld\n", buffer->size(), buffer->alignment());
    EXPECT_NE(buffer, nullptr);
    auto memory_factory = MemoryFactory(device);
    Memory *memory = nullptr;
    memory = memory_factory.create_buffer_memory(buffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, 32);
    EXPECT_NE(memory, nullptr);
    
    if(buffer) {
        delete buffer;
    }

    if(memory) {
        delete memory;
    }
}

TEST(EV_BUFFER_TEST, BUFFER_CREATE_TEST) {
    auto factory = BufferFactory(device);
    Buffer *buffer = nullptr;
    buffer = factory.create_buffer(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 1024);
    EXPECT_NE(buffer, nullptr);
    delete buffer;
}

#endif