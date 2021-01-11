package(default_visibility = ["//visibility:public"])

load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@python_tools_deps//:requirements.bzl", "requirement")

py_test(
    name = "test_hermetic_python_environment",
    srcs = ["test_hermetic_python_environment.py"],
)

py_library(
    name = "proto_log",
    srcs = ["proto_log.py"],
    deps = [
        "//software/proto:software_py_proto",
        requirement("protobuf"),
    ],
)

py_library(
    name = "sensor_proto_log",
    srcs = ["sensor_proto_log.py"],
    deps = [
        ":proto_log",
        "//software/proto:software_py_proto",
    ],
)

pybind_extension(
    name = "cost_function_python_wrapper",
    srcs = ["cost_function_python_wrapper.cpp"],
)

py_library(
    name = "cost_function_python_wrapper",
    data = [":cost_function_python_wrapper.so"],
)

py_binary(
    name = "jupyter",
    srcs = ["jupyter.py"],
    # glob all the notebooks in this directory
    data = [":notebooks"],
    deps = [
        requirement("jupyter"),
        requirement("notebook"),
        requirement("numpy"),
        requirement("matplotlib"),
        requirement("plotly"),
        ":proto_log",
        ":sensor_proto_log",
        ":cost_function_python_wrapper",
        "//shared/proto:tbots_py_proto",
        "//software/proto:software_py_proto",
    ],
)
