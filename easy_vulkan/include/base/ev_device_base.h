#ifndef __EV_DEVICE_BASE_RESOURCE_H__
#define __EV_DEVICE_BASE_RESOURCE_H__

#include "ev_device.h"
#include <cassert>

namespace EasyVulkan {
    class DeviceBase {
        
        protected:

        Device *_device = nullptr;

        public:

        explicit DeviceBase(Device *device);

        Device* device();
    };
}

#endif