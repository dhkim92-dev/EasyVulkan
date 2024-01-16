#ifndef __EV_TEST_MAIN_CPP__
#define __EV_TEST_MAIN_CPP__

#include "easy_vulkan.h"
#include "ev_instance_test.hpp"
#include "ev_device_test.hpp"
#include "ev_buffer_test.hpp"
#include "ev_image_test.hpp"
#include "ev_command_pool_test.hpp"
#include "ev_command_buffer_test.hpp"
#include "ev_shader_test.hpp"

Instance *instance = nullptr;
Device *device = nullptr;
CommandPool *command_pool = nullptr;

DEFAULT_TEST_MAIN()

#endif