cmake_minimum_required(VERSION 3.10)
SET(EASY_VULKAN_HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
SET(EASY_VULKAN_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
SET(OS ${CMAKE_SYSTEM_NAME}) 

MESSAGE("Operating System ${OS}")

add_definitions(-DNDEBUG)
IF(${OS} STREQUAL Windows)
    MESSAGE("[easy-vulkan] Build System Windows")
ELSEIF(${OS} STREQUAL Darwin)
    MESSAGE("[easy-vulkan] Build System MacOS")
    INCLUDE_DIRECTORIES(${EASY_VULKAN_HEADER_DIR} ${VULKAN_SDK}/include)
    LINK_DIRECTORIES(${VULKAN_SDK}/lib)
    LINK_LIBRARIES(vulkan)
ELSEIF(${OS} STREQUAL Linux) 
    MESSAGE("[easy-vulkan] Build System Linux")
    INCLUDE_DIRECTORIES(/usr/include /usr/local/include ${EASY_VULKAN_HEADER_DIR})
    LINK_DIRECTORIES(/usr/local/lib /usr/lib)
    LINK_LIBRARIES(vulkan)
ELSE() 
    MESSAGE("[easy-vulkan] Not Supported Platform.")
ENDIF()

FILE(GLOB EASY_VULKAN_CORE_SOURCE src/*.cpp)
FILE(GLOB EASY_VULKAN_CORE_HEADER include/*.h)

ADD_LIBRARY(${CMAKE_PROJECT_NAME} SHARED
    ${EASY_VULKAN_CORE_HEADER}
    ${EASY_VULKAN_CORE_SOURCE}
)

FILE(COPY ${EASY_VULKAN_HEADER_DIR} DESTINATION ${PROJECT_SOURCE_DIR}/build/easy_vulkan/)

# set_target_properties(easy_vulkan_core PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
# set_target_properties(easy_vulkan_core PROPERTIES SOVERSION 0)
# target_include_directories(easy-vulkan PUBLIC include)
# target_include_directories(easy_vulkan_core PRIVATE src)
