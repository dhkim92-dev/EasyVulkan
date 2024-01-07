#ifndef __EV_INSTANCE_CI_H__
#define __EV_INSTANCE_CI_H__

#include <string>
#include <vector>
#include <vulkan/vulkan.h>

using namespace std;

namespace EasyVulkan {
    namespace Initializer {
        /**
         * @brief VkApplicationInfo Builder class
        */
        class ApplicationInfo {

            uint32_t _api_version=VK_API_VERSION_1_0;

            string _app_name="Easy Vulkan";

            uint32_t _app_version=VK_MAKE_VERSION(1, 0, 0);

            string _engine_name="Easy Vulkan";

            uint32_t _engine_version=VK_MAKE_VERSION(1, 0, 0);

            void *_next = NULL;

        public:
            ApplicationInfo* api_version(uint32_t value); 

            ApplicationInfo* app_name(string value); 

            ApplicationInfo* app_version(uint32_t value); 

            ApplicationInfo* engine_name(string value); 

            ApplicationInfo* engine_version(uint32_t value); 

            ApplicationInfo* next(void *ptr); 

            VkApplicationInfo build();
        };

        /**
         * @brief VkInstanceCreateInfo builder 
        */
        class InstanceCreateInfo {

            vector<const char *> extensions;

            vector<const char *> validations;

            VkInstanceCreateFlags _flags;

            ApplicationInfo *app_info;

            VkApplicationInfo vk_app_info;

            void *_next = NULL;

            public:

            InstanceCreateInfo* application_info(ApplicationInfo *info);

            InstanceCreateInfo* device_extensions(vector<const char *> value);
            
            InstanceCreateInfo* validation_layers(vector<const char *> value);

            InstanceCreateInfo* flags(VkInstanceCreateFlags value);

            InstanceCreateInfo* next(void *ptr);

            VkInstanceCreateInfo build();
        };
    }
}


#endif