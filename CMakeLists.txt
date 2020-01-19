cmake_minimum_required(VERSION 3.15)

project(python_sdk_wrapper)

set(CMAKE_CXX_STANDARD 17)

find_package(PythonLibs 3.8 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(python_sdk_wrapper SHARED rplidar_python/main.cpp)
set_target_properties(
        python_sdk_wrapper
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "rplidar_python"
        LINKER_LANGUAGE C
)

target_link_libraries(python_sdk_wrapper ${PYTHON_LIBRARIES})