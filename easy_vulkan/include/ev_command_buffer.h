#ifndef __EV_COMMAND_BUFFER_H__
#define __EV_COMMAND_BUFFER_H__

#include <vulkan/vulkan.h>
#include "ev_buffer.h"
#include "ev_command_pool.h"

namespace EasyVulkan {

    class CommandBuffer : DeviceBase {

        CommandPool* _command_pool = nullptr;

        VkCommandBuffer _command_buffer = VK_NULL_HANDLE;

        public :

        explicit CommandBuffer(Device *device, CommandPool *command_pool);

        ~CommandBuffer();

        VkResult create();

        // begin of phase

        VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, 
            VkCommandBufferInheritanceInfo *inheritance_info_ptr = nullptr, 
            void *next_ptr = nullptr);

        void begin_render_pass(VkRenderPass render_pass, VkFramebuffer frame_buffer, VkRect2D render_area , VkClearValue clear_color = {{0.0f, 0.0f, 0.0f, 1.0f}});

        // copy resources

        void copy_buffer(Buffer *src, Buffer *dst, uint32_t src_offset, uint32_t dst_offset, uint32_t size);

        //binding resources

        void bind_vertex_buffer(Buffer *vertices, uint32_t first, uint32_t binding_count, VkDeviceSize *p_binding);

        void bind_index_buffer(Buffer *indices, VkDeviceSize offset, VkIndexType type = VK_INDEX_TYPE_UINT32);

        void bind_descriptor_sets();

        void bind_pipeline();

        // draw 

        void draw(uint32_t vertex_count, uint32_t instance_count=1, uint32_t first_vertex=0, uint32_t first_instance=0);

        //end of phase

        void end_render_pass();

        VkResult end();

        VkCommandBuffer command_buffer();

        VkCommandBuffer& command_buffer_alias();

        VkCommandBuffer* command_buffer_ptr();

        CommandPool* command_pool();

        void release();
    };
}

#endif