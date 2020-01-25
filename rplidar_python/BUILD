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
    outs = ["rplidar_sdk-0.1.0-py3-none-any.whl"],
    cmd = """
    BASE_DIR=$$(pwd)
    mkdir $(@D)/tmp &&
    mkdir $(@D)/tmp/rplidar_sdk &&
    cp $(location :_python_sources) $(@D)/tmp/rplidar_sdk &&
    cp $(location :_native_extension) $(@D)/tmp/rplidar_sdk &&
    cp $(location pyproject.toml) $(@D)/tmp &&
    touch $(@D)/tmp/rplidar_sdk/__init__.py &&
    echo "leaving $$PWD and entering temp"
    cd $(@D)/tmp &&
    poetry build --no-interaction --verbose &&
    echo "directory listing"
    ls */**
    echo "leaving tmp"
    cd $$BASE_DIR &&
    echo "ls tmp/dist/rplidar_sdk-0.1.0-py3-none-any.whl" &&

    ls $(@D)/tmp/dist/rplidar_sdk-0.1.0-py3-none-any.whl &&
    cp $(@D)/tmp/dist/rplidar_sdk-0.1.0-py3-none-any.whl $(@D) &&
    rm -rf $(@D)/tmp
     """,
    #    cmd = "ls $(location bindings/rplidar_sdk.py)",
    #    cmd = " echo \"$@\"",
)
