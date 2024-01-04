#ifndef __EV_DEBUG_H__
#define __EV_DEBUG_H__

#include <vulkan/vulkan.h>
#include <string>
#include "ev_utility.h"

using namespace std;

namespace EasyVulkan 
{
    namespace Debug 
    {

        /**
         * @brief default message callback function
        */
        VKAPI_ATTR VkBool32 VKAPI_CALL debug_messege_callback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT object_type,
            uint64_t src,
            size_t location,
            int32_t message_code,
            const char *layer_prefix,
            const char *message,
            void *user_data
        );

        void setup_debugging(VkInstance instance);

        void free_debug_callback(VkInstance instance);
    }

    // namespace Debugger {
        // void setup(VkInstance instance);
    // }
}

#endif