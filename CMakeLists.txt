cmake_minimum_required(VERSION 3.28)
project(UDP_LowBandwidth)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE SOURCES_COMM "src/impl/common/*.cpp")
file(GLOB_RECURSE HEADERS_PUB "include/udplb/*.h")
file(GLOB_RECURSE HEADERS_PRIV "src/headers/*.h")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB_RECURSE SOURCES_PLATFORM "src/impl/linux/*.cpp")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB_RECURSE SOURCES_PLATFORM "src/impl/windows/*.cpp")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_library(UDP_LowBandwidth SHARED ${SOURCES_COMM} ${SOURCES_PLATFORM} ${HEADERS_PUB} ${HEADERS_PRIV})

target_include_directories(UDP_LowBandwidth PUBLIC include/udplb PRIVATE src/headers)

# Testing (we only want to test if -DTESTING is passed)
if (TESTING)
    add_subdirectory(test)
endif ()
