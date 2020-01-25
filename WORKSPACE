# Creates a repository rule for the system python headers.
# pybind11.BUILD depends on this repository rule to detect your python configuration
load("//third_party/pybind11_bazel:python_configure.bzl", "python_configure")

python_configure(name = "local_config_python")

# Create pybind11 external repository
# If using another pybind11 version:
# Use tar URL of desired version, change strip_prefix to your version "pybind11-x.x.x",
# Supply correct sha256 for your version.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "pybind11",
    build_file = "@//third_party/pybind11_bazel:pybind11.BUILD",
    sha256 = "1eed57bc6863190e35637290f97a20c81cfe4d9090ac0a24f3bbf08f265eb71d",
    strip_prefix = "pybind11-2.4.3",
    url = "https://github.com/pybind/pybind11/archive/v2.4.3.tar.gz",
)

# @rules_python repository, used to create python build targets
http_archive(
    name = "rules_python",
    sha256 = "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.1/rules_python-0.0.1.tar.gz",
)

# Currently does nothing, futureproofs your core Python rule dependencies.
load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

# Pulls in dependencies needed to use the python packaging rules.
load("@rules_python//python:pip.bzl", "pip_repositories")

pip_repositories()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rp_lidar",
    commit = "5438c00be023cb477c9b26b85428184df6632055",
    remote = "https://github.com/theunkn0wn1/rplidar_sdk.git",
)

http_archive(
    name = "io_bazel_rules_wheel",
    sha256 = "89693425c2c81e31b9956670a9b0adc5a6fe8aa8",
    strip_prefix = "rules_wheel-89693425c2c81e31b9956670a9b0adc5a6fe8aa8",
    urls = ["https://github.com/georgeliaw/rules_wheel/archive/89693425c2c81e31b9956670a9b0adc5a6fe8aa8.tar.gz"],
)

git_repository(
    name = "io_bazel_rules_wheel",
    commit = "89693425c2c81e31b9956670a9b0adc5a6fe8aa8",
    remote = "https://github.com/georgeliaw/rules_wheel.git",
    shallow_since = "1551369477 -0800",
)
