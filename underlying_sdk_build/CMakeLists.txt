

file(GLOB base_sources ../third_party/rplidar_sdk/sdk/sdk/src/*.cpp ../third_party/rplidar_sdk/sdk/sdk/src/hal/*.cpp)
file(GLOB base_includes ../third_party/rplidar_sdk/sdk/sdk/src/*.h ../third_party/rplidar_sdk/sdk/sdk/src/*.hpp ../third_party/rplidar_sdk/sdk/sdk/src/hal/*.h ../third_party/rplidar_sdk/sdk/sdk/src/hal/*.hpp)

# Check if Windows, exclude MinGW
if (WIN32 AND NOT MINGW)
    message(STATUS "Detected Windows target...")
    file(GLOB platform_srcs ../third_party/rplidar_sdk/sdk/sdk/src/arch/win32/*.hpp ../third_party/rplidar_sdk/sdk/sdk/src/arch/win32/*.cpp)
    include_directories(../third_party/rplidar_sdk/sdk/sdk/src/arch/win32)
elseif (MINGW)
    # Library doesn't build under MinGW, no idea why.
    message(FATAL_ERROR "Mingw is presently not supported.")
elseif (${CMAKE_SYSTEM_NAME} MATCHES Linux)
    message(STATUS "linux target...")
    file(GLOB platform_srcs ../third_party/rplidar_sdk/sdk/sdk/src/arch/linux/*.hpp ../third_party/rplidar_sdk/sdk/sdk/src/arch/linux/*.cpp)
    include_directories(../third_party/rplidar_sdk/sdk/sdk/src/arch/linux)

elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message(STATUS "Apple Mac OS X target...")
    file(GLOB platform_srcs ../third_party/rplidar_sdk/sdk/sdk/src/arch/macOS/*.hpp ../third_party/rplidar_sdk/sdk/sdk/src/arch/macOS/*.cpp)
    include_directories(../third_party/rplidar_sdk/sdk/sdk/src/arch/macOS)
else ()
    message(FATAL_ERROR "Unknown platform ${CMAKE_SYSTEM_NAME}, build cannot continue.")
endif ()


# glob shared C++ sources
add_library(rplidar_sdk SHARED ${base_sources} ${platform_srcs})
include_directories(src ../third_party/rplidar_sdk/sdk/sdk/src/hal include)

install(TARGETS rplidar_sdk DESTINATION rplidar_sdk)