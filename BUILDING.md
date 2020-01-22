# Building
This project is built using [Bazel](https://docs.bazel.build/versions/master/install.html) , install it before continuing.

## prerequisites
- Git
- cpython >= 3.5
- cpython dev headers

# 1. init submodules
```bash
git submodule update --init
```

# 2. invoke bazel
```bash
bazel build //rplidar_python/bindings:rplidar_sdk.so
```