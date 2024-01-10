#ifndef __EV_COMMAND_BUFFER_CPP__
#define __EV_COMMAND_BUFFER_CPP__

#include "ev_command_buffer.h"

using namespace EasyVulkan;

CommandBuffer::CommandBuffer(Device *device, CommandPool *command_pool) 
: DeviceBase(device) {
    _command_pool = command_pool;
    create();
}

CommandBuffer::~CommandBuffer() {
    release();
}

VkResult CommandBuffer::create() {
    if(_command_buffer != VK_NULL_HANDLE) {
        return VK_SUCCESS;
    }

    VkCommandBufferAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.commandBufferCount = 1;
    info.commandPool = _command_pool->command_pool();
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.pNext = nullptr;

    return vkAllocateCommandBuffers(_device->device(), &info, &_command_buffer);
}

// Begin of Phase

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags, 
    VkCommandBufferInheritanceInfo *inheritance_info_ptr, 
    void *next_ptr) {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pInheritanceInfo = inheritance_info_ptr;
    info.pNext = next_ptr;
    info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    return vkBeginCommandBuffer(_command_buffer, &info);
}

void CommandBuffer::begin_render_pass(VkRenderPass render_pass,
    VkFramebuffer frame_buffer,
    VkRect2D render_area,
    VkClearValue clear_color) {
    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.framebuffer = frame_buffer;
    info.renderArea = render_area;
    info.clearValueCount = 1;
    info.pClearValues = &clear_color;

    return vkCmdBeginRenderPass(_command_buffer, &info, VK_SUBPASS_CONTENTS_INLINE);
}

// Copy Resources

void CommandBuffer::copy_buffer(Buffer *src, Buffer *dst, uint32_t src_offset, uint32_t dst_offset, uint32_t size) {
    VkBufferCopy region = {src_offset, dst_offset, size};
    vkCmdCopyBuffer(_command_buffer, src->buffer(), dst->buffer(), 1, &region);
}

// Bind Resources

void CommandBuffer::bind_vertex_buffer(Buffer *vertices, uint32_t first, uint32_t binding, VkDeviceSize *p_binding) {
    vkCmdBindVertexBuffers(_command_buffer, first, binding, vertices->buffer_ptr(), p_binding);
}

void CommandBuffer::bind_index_buffer(Buffer *indices, VkDeviceSize offset, VkIndexType type) {
    vkCmdBindIndexBuffer(_command_buffer, indices->buffer(), offset, type);
}

// End of Phase

void CommandBuffer::end_render_pass() {
    return vkCmdEndRenderPass(_command_buffer);
}

VkResult CommandBuffer::end() {
    return vkEndCommandBuffer(_command_buffer);
}

CommandPool* CommandBuffer::command_pool() {
    return _command_pool;
}

VkCommandBuffer CommandBuffer::command_buffer() {
    return _command_buffer;
}

VkCommandBuffer& CommandBuffer::command_buffer_alias() {
    return _command_buffer;
}

VkCommandBuffer* CommandBuffer::command_buffer_ptr() {
    return &_command_buffer;
}

void CommandBuffer::release() {
    if(_command_buffer != VK_NULL_HANDLE) {
        vkFreeCommandBuffers(_device->device(), _command_pool->command_pool(), 1, &_command_buffer);
        _command_buffer = VK_NULL_HANDLE;
    }
}

#endif