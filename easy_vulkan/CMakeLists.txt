cmake_minimum_required(VERSION 3.10)
set(EASY_VULKAN_HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(EASY_VULKAN_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(OS ${CMAKE_SYSTEM_NAME}) 

message("Operating System ${OS}")

add_definitions(-DNDEBUG)
if(${OS} STREQUAL Windows)
    message("[easy-vulkan] Build System Windows")
elseif(${OS} STREQUAL Darwin)
    message("[easy-vulkan] Build System MacOS")
    include_directories(${EASY_VULKAN_HEADER_DIR} /usr/local/include /usr/include)
    link_directories(/usr/local/lib /usr/lib)
    link_libraries(vulkan)
elseif(${OS} STREQUAL Linux) 
    message("[easy-vulkan] Build System Linux")
    include_directories(/usr/include /usr/local/include ${EASY_VULKAN_HEADER_DIR})
    link_directories(/usr/local/lib /usr/lib)
    link_libraries(vulkan)
elseif() 
    message("[easy-vulkan] Not Supported Platform.")
endif()

file(GLOB EASY_VULKAN_CORE_SOURCE src/*.cpp src/**/*.cpp)
file(GLOB EASY_VULKAN_CORE_HEADER include/*.h include/**/*.h)

add_library(${CMAKE_PROJECT_NAME} SHARED
    ${EASY_VULKAN_CORE_HEADER}
    ${EASY_VULKAN_CORE_SOURCE}
)

file(COPY ${EASY_VULKAN_HEADER_DIR} DESTINATION ${PROJECT_SOURCE_DIR}/build/easy_vulkan/)

# set_target_properties(easy_vulkan_core PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
# set_target_properties(easy_vulkan_core PROPERTIES SOVERSION 0)
# target_include_directories(easy-vulkan PUBLIC include)
# target_include_directories(easy_vulkan_core PRIVATE src)
