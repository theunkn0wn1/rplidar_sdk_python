filegroup(
    name = "_native_extension",
    srcs = [
        "//rplidar_python/bindings:_rplidar_sdk.so",
    ],
)

filegroup(
    name = "_python_sources",
    srcs = [
        "//rplidar_python/bindings:rplidar_sdk.py",
    ],
)

genrule(
    name = "build_wheel",
    srcs = [
        ":_native_extension",
        ":_python_sources",
        "pyproject.toml",
    ],
    outs = ["bindings-0.1.0-py3-none-any.whl"],
    cmd = """
    BASE_DIR=$$(pwd)
    mkdir $(@D)/tmp &&
    cp $(location :_python_sources) $(@D)/tmp &&
    cp $(location :_native_extension) $(@D)/tmp &&
    cp $(location pyproject.toml) $(@D) &&
    touch $(@D)/tmp/__init__.py &&
    echo "leaving $$PWD and entering temp"
    cd $(@D) &&
    poetry build --no-interaction --verbose &&
    echo "directory listing"
    ls */**
    echo "leaving tmp"
    cd $$BASE_DIR &&
    echo "ls dist/bindings-0.1.0-py3-none-any.whl" &&

    ls $(@D)/dist/bindings-0.1.0-py3-none-any.whl &&
    cp $(@D)/dist/bindings-0.1.0-py3-none-any.whl $(@D) &&
    rm -rf $(@D)/tmp
     """,
    #    cmd = "ls $(location bindings/rplidar_sdk.py)",
    #    cmd = " echo \"$@\"",
)
