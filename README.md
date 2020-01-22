# rplidar_python

This package aims to provide python bindings 
around the [Slamtek rplidar sdk ](https://github.com/theunkn0wn1/rplidar_sdk_python) for interacting with their lidars. 

## Installing
TODO bdist_wheel
 - one can probably copy the `.so` build artefact out of `bazel-bin/rplidar_python/bindings/rplidar_sdk.so`

## Hardware compatability
This library should be compatabile with anything the official 
C++ SDK supports, though specific testing has only been done against the A2.

## Python version compatibility
In theory this should work for modern Python versions >= 3.5.

