//
// Created by orion on 1/21/20.
//

#ifndef RPLIDAR_PYTHON_MAIN_H
#define RPLIDAR_PYTHON_MAIN_H
#include "pybind11/embed.h"
#include <rplidar.h>
namespace py = pybind11;

int add(int i, int j) { return i + j; }

#endif // RPLIDAR_PYTHON_MAIN_H
