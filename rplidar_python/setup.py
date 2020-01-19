from setuptools import setup, Extension

setup(name = "rplidar_python",
      version = "0.1",
      ext_modules = [Extension("rplidar_python", ["main.cpp"])]
      );
