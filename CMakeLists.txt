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

#####################
# Find rplidar_sdk
###################

include(ExternalProject)
ExternalProject_Add (
        rplidar_sdk_project
        GIT_REPOSITORY "https://github.com/theunkn0wn1/rplidar_sdk"
        GIT_TAG "origin/feature/cmake"
        PREFIX dependencies/rplidar_sdk
)
ExternalProject_Get_Property(rplidar_sdk_project install_dir)
add_library(rplidar_sdk SHARED IMPORTED)
set_property(TARGET rplidar_sdk PROPERTY IMPORTED_LOCATION ${install_dir}/lib/librplidar_sdk)

add_dependencies(rplidar_sdk rplidar_sdk_project)
include_directories(${install_dir}/include)

######################
# primary target
####################

add_library(python_sdk_wrapper SHARED rplidar_python/main.cpp)
set_target_properties(
        python_sdk_wrapper
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "rplidar_python"
        LINKER_LANGUAGE C
)
message(STATUS "python include dirs = " "${PYTHON_INCLUDE_DIRS}" " libraries = '${PYTHON_LIBRARIES}'")
include_directories(${PYTHON_INCLUDE_DIRS} ${rplidar_sdk_INCLUDE_DIRS})

target_link_libraries(python_sdk_wrapper ${PYTHON_LIBRARIES} ${rplidar_sdk_LIBRARIES})