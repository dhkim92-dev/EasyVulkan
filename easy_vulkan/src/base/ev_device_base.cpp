#ifndef __EV_DEVICE_BASE_RESOURCE_CPP__
#define __EV_DEVICE_BASE_RESOURCE_CPP__

#include "base/ev_device_base.h"

using namespace EasyVulkan; 

DeviceBase::DeviceBase(Device *device) : _device(device) {
    assert(_device != nullptr);
}

Device* DeviceBase::device() {
    return _device;
}

#endif