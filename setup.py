
# -*- coding: utf-8 -*-

from __future__ import print_function

import sys

try:
    from skbuild import setup
    from setuptools import find_packages
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

setup(
    name="rplidar_python",
    packages=find_packages(where = 'src'),
    version="0.1.0",
    package_dir={'': 'src'},
    description="Bindings to the Slamtech/rplidar_sdk",
    cmake_install_dir='src/rplidar_python',
    author="Joshua Salzedo",
    include_package_data = True,
)