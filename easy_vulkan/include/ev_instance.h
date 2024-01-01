#ifndef __EASY_VULKAN_INSTANCE_H__
#define __EASY_VULKAN_INSTANCE_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "ev_utility.h"

using namespace std;

/**
 * @namespace EasyVulkan namespace
 * @brief Default Namespace
*/
namespace EasyVulkan {
    
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

        vector<char *> extensions;

        vector<char *> validations;

        VkInstanceCreateFlags _flags;

        ApplicationInfo *app_info = nullptr;

        void *_next = NULL;

        public:

        InstanceCreateInfo* application_info(ApplicationInfo *info);

        InstanceCreateInfo* device_extensions(vector<char *> value);
        
        InstanceCreateInfo* validation_layers(vector<char *> value);

        InstanceCreateInfo* flags(VkInstanceCreateFlags value);

        InstanceCreateInfo* next(void *ptr);

        VkInstanceCreateInfo build();
    };


    /**
     * @class Instance
     * @brief Vulkan Instance Wrapper
    */
    class Instance {
        
        vector<char *> _extensions; /*! instance extensions that want to be enabled */

        vector<char *> _validation_layers; /*! validation layers that want to be enabled*/

        VkInstance _instance = NULL; /*! VkInstance */

        void setup_extensions(vector<string> &requests);

        void setup_validation_layers(vector<string> &requests);

        public:

        /**
        * @brief constructor of Instance
        * @details EasyVulkan Instance Constructor. It should be include VkInstanceExtensions and Validation Layers that want to enable.
        */
        explicit Instance(vector<string> extensions, vector<string> validation_layers);

        ~Instance();

        void create(ApplicationInfo *app_info, VkInstanceCreateFlags flags = VK_FLAGS_NONE);
        
        /**
         * @brief VkInstance getter
        */
        VkInstance instance();

        /**
         * @brief getter of Instance Extension names list
        */
        vector<char *> extensions();

        /**
         * @brief geter of Vulkan Validation layers name list
        */
        vector<char *> validation_layers();
    };
}

#endif