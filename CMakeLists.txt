cmake_minimum_required(VERSION 3.12)

project(python_sdk_wrapper)

set(CMAKE_CXX_STANDARD 17)

find_package(Python 3.8 REQUIRED Interpreter)

if( Python_FOUND )
    include_directories( ${PYTHON_INCLUDE_DIRS} )
else()
    message( FATAL_ERROR "Python libraries not found" )
endif()
find_package(PythonInterp 3.8 REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)

add_library(python_sdk_wrapper SHARED rplidar_python/main.cpp)
set_target_properties(
        python_sdk_wrapper
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "rplidar_python"
        LINKER_LANGUAGE C
)
message(STATUS "python include dirs = " "${PYTHON_INCLUDE_DIRS}" " libraries = '${PYTHON_LIBRARIES}'")
include_directories(${PYTHON_INCLUDE_DIRS})

target_link_libraries(python_sdk_wrapper ${PYTHON_LIBRARIES})