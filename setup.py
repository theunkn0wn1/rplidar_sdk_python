
# -*- coding: utf-8 -*-

from __future__ import print_function

import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

setup(
    name="rplidar_sdk",
    version="0.0.2",
    description="a minimal example package (with pybind11)",
    author="Joshua Salzedo",
    license="",
    packages=["rplidar_python"],
    package_dir={"": ""},
    cmake_install_dir="src/rplidar_sdk",
)