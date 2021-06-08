# rplidar_python

This package aims to provide python bindings 
around the [Slamtek rplidar sdk ](https://github.com/theunkn0wn1/rplidar_sdk_python) for interacting with their lidars. 

## Installing
As this is a native python extension, build tools will be required on the host.
cmake, git, and a suitable compiler are required.

```shell
git clone https://github.com/theunkn0wn1/rplidar_sdk_python --recursive
cd rplidar_sdk_python
pip install .
```

## Hardware compatability
This library should be compatible with anything the official 
C++ SDK supports, though specific testing has only been done against the A2.

## Python version compatibility
In theory this should work for modern Python versions >= 3.5.

