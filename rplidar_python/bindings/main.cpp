#include <Python.h>
#include <rplidar.h>
// This is the definition of a method
static PyObject *division(PyObject *self, PyObject *args) {
  long dividend, divisor;
  if (!PyArg_ParseTuple(args, "ll", &dividend, &divisor)) {
    return nullptr;
  }
  if (0 == divisor) {
    PyErr_Format(PyExc_ZeroDivisionError, "Dividing %d by zero!", dividend);
    return nullptr;
  }
  return PyLong_FromLong(dividend / divisor);
}
static PyObject *create_Driver(PyObject *self, PyObject *args) {
  rp::standalone::rplidar::RPlidarDriver::CreateDriver();

  Py_RETURN_NONE;
}
// Exported methods are collected in a table
PyMethodDef method_table[] = {
    {"division", (PyCFunction)division, METH_VARARGS, "Method docstring"},
    {"create_driver", (PyCFunction)create_Driver, METH_VARARGS,
     "create a driver"},
    {nullptr, nullptr, 0, nullptr} // Sentinel value ending the table
};
// A struct contains the definition of a module
PyModuleDef rplidar_python_module = {
    PyModuleDef_HEAD_INIT,
    "rplidar_sdk", // Module name
    "This is the module docstring",
    -1, // Optional size of the module state memory
    method_table,
    nullptr, // Optional slot definitions
    nullptr, // Optional traversal function
    nullptr, // Optional clear function
    nullptr  // Optional module deallocation function
};

// The module init function
PyMODINIT_FUNC PyInit_rplidar_sdk(void) {
  return PyModule_Create(&rplidar_python_module);
}
