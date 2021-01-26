cmake_minimum_required(VERSION 3.15...3.18)

project(rplidar_python VERSION "0.0.1")

# Currently, Scikit-build does not support FindPython, so we convert the
# provided hints ourselves.
if(SKBUILD)
  set(Python_EXECUTABLE "${PYTHON_EXECUTABLE}")
  set(Python_INCLUDE_DIR "${PYTHON_INCLUDE_DIR}")
  set(Python_LIBRARY "${PYTHON_LIBRARY}")
  set(DUMMY "${PYTHON_VERSION_STRING}")  # Not needed, silences a warning
endif()

set(Python_FIND_IMPLEMENTATIONS CPython PyPy)  # PyPy requires 3.18
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Scikit-Build does not add your site-packages to the search path automatically,
# so we need to add it _or_ the pybind11 specific directory here.
execute_process(
  COMMAND
    "${Python_EXECUTABLE}" -c
    "import pybind11; print(pybind11.get_cmake_dir())"
  OUTPUT_VARIABLE _tmp_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
list(APPEND CMAKE_PREFIX_PATH "${_tmp_dir}")

add_subdirectory(third_party/pybind11)
add_subdirectory(third_party/rplidar_sdk)
# Now we can find pybind11
#find_package(pybind11 CONFIG REQUIRED)

Python_add_library(_core MODULE rplidar_python/bindings/main.cpp rplidar_python/bindings/main.h)
target_link_libraries(_core PUBLIC rplidar_sdk pybind11::headers pybind11::module)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
install(TARGETS _core DESTINATION .)
