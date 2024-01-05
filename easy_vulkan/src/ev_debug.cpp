#ifndef __EV_DEBUG_CPP__
#define __EV_DEBUG_CPP__

#include <sstream>
#include "ev_debug.h"

namespace EasyVulkan 
{
    namespace Debug 
    {
        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
		VkDebugUtilsMessengerEXT debugUtilsMessenger = VK_NULL_HANDLE;

        VKAPI_ATTR VkBool32 VKAPI_CALL debug_utils_messenger_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
            void *user_data
        ) {
            stringstream ss;
            ss << "[" << callback_data->messageIdNumber << "][" << callback_data->pMessageIdName << "] : " << callback_data->pMessage;
            if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                LOGV("\n[Vulkan Validation] : %s", ss.str().c_str());
            }else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
                LOGI("\n[Vulkan Validation] : %s", ss.str().c_str());
            }else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                LOGW("\n[Vulkan Validation] : %s", ss.str().c_str());
            }else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                LOGE("\n[Vulkan Validation] : %s", ss.str().c_str());
            }

            return VK_FALSE;
        }

        void setup_debugging(VkInstance instance) {
            vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
            vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

            VkDebugUtilsMessengerCreateInfoEXT ci{};
            ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            ci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
            ci.pfnUserCallback = debug_utils_messenger_callback;
            CHECK_VK_RESULT(vkCreateDebugUtilsMessengerEXT(instance, &ci, nullptr, &debugUtilsMessenger));
        }

        void free_debug_callback(VkInstance instance) {
            if(debugUtilsMessenger != VK_NULL_HANDLE) {
                vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
                debugUtilsMessenger = VK_NULL_HANDLE;
            }
        }
    }

    // namespace Debugger 
    // {
    //     PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT{ nullptr };
	// 	PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT{ nullptr };
	// 	PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT{ nullptr };

    //     void setup(VkInstance instance) {
    //         vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdBeginDebugUtilsLabelEXT"));
    //         vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdEndDebugUtilsLabelEXT"));
    //         vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdInsertDebugUtilsLabelEXT"));
    //     }

        
    // }
}

#endif