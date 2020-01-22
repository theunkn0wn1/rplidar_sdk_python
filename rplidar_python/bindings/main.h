//
// Created by orion on 1/21/20.
//

#ifndef RPLIDAR_PYTHON_MAIN_H
#define RPLIDAR_PYTHON_MAIN_H
#include "pybind11/embed.h"

namespace py = pybind11;

int add(int i, int j) { return i + j; }
bool is_ok(uint32_t);
bool is_fail(uint32_t);



#endif // RPLIDAR_PYTHON_MAIN_H
