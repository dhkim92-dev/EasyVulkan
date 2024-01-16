cmake_minimum_required(VERSION 3.10)

project(easy-vulkan VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE true)
set(SHADERS_DIR_PATH ${PROJECT_SOURCE_DIR}/shaders/)

message("SHADER DIR PATH : ${SHADERS_DIR_PATH}")
file(COPY ${SHADERS_DIR_PATH} DESTINATION ${PROJECT_SOURCE_DIR}/build/shaders/)

add_subdirectory(easy_vulkan)
add_subdirectory(test)
add_subdirectory(externals/glfw glfw)