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
        vector<const char *> _extensions; /*! instance extensions that want to be enabled */

        vector<const char *> _validation_layers; /*! validation layers that want to be enabled*/

        VkInstance _instance = VK_NULL_HANDLE; /*! VkInstance */

        bool _debug = false;

        void setup_extensions(vector<const char *> &requests);

        void setup_validation_layers(vector<const char *> &requests);

        public:
        
        /**
        * @brief constructor of Instance
        * @details EasyVulkan Instance Constructor. It should be include VkInstanceExtensions and Validation Layers that want to enable.
        */
        explicit Instance(vector<const char *>, vector<const char *> validation_layers);

        ~Instance();

        void create(Info::ApplicationInfo *app_info, VkInstanceCreateFlags flags = VK_FLAGS_NONE);

        /**
         * @brief VkInstance getter
        */
        VkInstance instance();

        /**
         * @brief getter of Instance Extension names list
        */
        vector<const char *> extensions();

        /**
         * @brief getter of Vulkan Validation layers name list
        */
        vector<const char *> validation_layers();

        /**
         * @brief setter of Vulkan validation layer enabled or disabled
        */
        void set_debug(bool value);

        /**
         * @brief getter of Vulkan validation layer enabled or disabled.
        */
        bool debug();
    };
}

#endif