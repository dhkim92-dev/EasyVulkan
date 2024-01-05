SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
SET(EASY_VULKAN_CORE_HEADER_DIRECTORY ${PROJECT_SOURCE_DIR}/build/easy_vulkan/include)
SET(EASY_VULKAN_CORE_LIBRARY_DIRECTORY ${PROJECT_SOURCE_DIR}/build/easy_vulkan/lib)
SET(GLFW_LIBRARY_DIRECTORY ${PROJECT_SOURCE_DIR}/build/glfw/src)
SET(GLFW_HEADER_DIRECTORY ${PROJECT_SOURCE_DIR}/externals/glfw/include)
add_definitions(-DNDEBUG)

MESSAGE("[easy-vulkan-test] core include path : ${EASY_VULKAN_CORE_HEADER_DIRECTORY}")
MESSAGE("[easy-vulkan-test] core library path : ${EASY_VULKAN_CORE_LIBRARY_DIRECTORY}")

IF(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    MESSAGE("[easy-vulkan-test] Build System Windows")
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    MESSAGE("[easy-vulkan-test] Build System MacOS")
    INCLUDE_DIRECTORIES(/usr/include /usr/local/include ${EASY_VULKAN_CORE_HEADER_DIRECTORY} include ${GLFW_HEADER_DIRECTORY}) 
    LINK_DIRECTORIES(/usr/local/lib /usr/lib ${EASY_VULKAN_CORE_LIBRARY_DIRECTORY} ${GLFW_LIBRARY_DIRECTORY})
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL LINUX) 
    MESSAGE("[easy-vulkan-test] Build System Linux")
    INCLUDE_DIRECTORIES(/usr/include /usr/local/include ${EASY_VULKAN_CORE_HEADER_DIRECTORY} include ${GLFW_HEADER_DIRECTORY}) 
    LINK_DIRECTORIES(/usr/local/lib /usr/lib ${EASY_VULKAN_CORE_LIBRARY_DIRECTORY} ${GLFW_LIBRARY_DIRECTORY})  
ENDIF()

LINK_LIBRARIES(vulkan gtest easy-vulkan)

FILE(GLOB EASY_VULKAN_TEST_FILES src/*.cpp)

FOREACH(F IN LISTS EASY_VULKAN_TEST_FILES)
    get_filename_component(FILE_NAME ${F} NAME)
    get_filename_component(BASE_NAME ${F} NAME_WE)

    ADD_EXECUTABLE(${BASE_NAME} src/${BASE_NAME}.cpp src/test_utility.hpp)
    target_include_directories(${BASE_NAME} PUBLIC ${EASY_VULKAN_CORE_HEADER_DIRECTORY})
    target_link_libraries(${BASE_NAME} easy-vulkan glfw)
ENDFOREACH()




