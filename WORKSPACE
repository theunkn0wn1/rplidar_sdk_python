workspace( name = "python_rplidar")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "pybind11",
    build_file = "@//third_party/pybind11_bazel:pybind11.BUILD",
    sha256 = "1eed57bc6863190e35637290f97a20c81cfe4d9090ac0a24f3bbf08f265eb71d",
    strip_prefix = "pybind11-2.4.3",
    url = "https://github.com/pybind/pybind11/archive/v2.4.3.tar.gz",
)

http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.1/rules_python-0.0.1.tar.gz",
    sha256 = "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161",
)
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()
# Only needed if using the packaging rules.
load("@rules_python//python:pip.bzl", "pip_repositories")
pip_repositories()