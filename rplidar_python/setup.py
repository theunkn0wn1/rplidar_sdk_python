from setuptools import setup, Extension

setup(name="rplidar_python",
      version="0.1",
        # FIXME all the necessary library bindings...
      ext_modules=[Extension(
          "rplidar_python",
          sources=["bindings/main.cpp"],
          include_dirs=["bindings/"]
      )
      ]
      )
