cmake_minimum_required(VERSION 3.10)

PROJECT(easy-vulkan VERSION 0.0.1)
SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE true)

add_subdirectory(easy_vulkan)
add_subdirectory(test)
add_subdirectory(externals/glfw glfw)