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
    outs = ["wheel_tmp"],
    cmd = """
    mkdir $(@D)/tmp &&
    cp $(location :_python_sources) $(@D)/tmp &&
    cp $(location :_native_extension) $(@D)/tmp &&
    ls $(@D)/tmp &&
    rm -rf $(@D)/tmp
     """,
    #    cmd = "ls $(location bindings/rplidar_sdk.py)",
    #    cmd = " echo \"$@\"",
)
