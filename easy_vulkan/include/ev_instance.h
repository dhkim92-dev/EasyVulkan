#ifndef __EASY_VULKAN_INSTANCE_H__
#define __EASY_VULKAN_INSTANCE_H__

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "builder/ev_instance_ci.h"
#include "ev_utility.h"

using namespace std;

/**
 * @namespace EasyVulkan namespace
 * @brief Default Namespace
*/
namespace EasyVulkan {
    /**
     * @class Instance
     * @brief Vulkan Instance Wrapper
    */
    class Instance {
        vector<char *> _extensions; /*! instance extensions that want to be enabled */

        vector<char *> _validation_layers; /*! validation layers that want to be enabled*/

        VkInstance _instance = VK_NULL_HANDLE; /*! VkInstance */

        void setup_extensions(vector<char *> &requests);

        void setup_validation_layers(vector<char *> &requests);

        public:
        
        /**
        * @brief constructor of Instance
        * @details EasyVulkan Instance Constructor. It should be include VkInstanceExtensions and Validation Layers that want to enable.
        */
        explicit Instance(vector<char *>, vector<char *> validation_layers);

        ~Instance();

        void create(Info::ApplicationInfo *app_info, VkInstanceCreateFlags flags = VK_FLAGS_NONE);

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