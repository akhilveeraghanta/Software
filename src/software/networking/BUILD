package(default_visibility = ["//visibility:public"])

genrule(
        name = "configured_network_interface",
        outs = ["configured_network_interface.h"],
        cmd = "\n".join([
            # we load the TBOTS_WIFI_INTERFACE env variable that is configured through `setup_networking.sh`
            "echo env[\'TBOTS_WIFI_INTERFACE\']".
            "mv out.h $@",
        ]),
        visibility = ["//visibility:private"],
)

cc_library(
    name = "proto_multicast_listener",
    hdrs = [
        "proto_multicast_listener.h",
        "proto_multicast_listener.tpp",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":configured_network_interface",
        "//software/logger",
        "@boost//:asio",
    ],
)

cc_library(
    name = "threaded_proto_multicast_listener",
    hdrs = [
        "threaded_proto_multicast_listener.h",
        "threaded_proto_multicast_listener.tpp",
    ],
    deps = [
        ":configured_network_interface",
        ":proto_multicast_listener",
        "@boost//:asio",
    ],
)

cc_library(
    name = "proto_multicast_sender",
    hdrs = [
        "proto_multicast_sender.h",
        "proto_multicast_sender.tpp",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":configured_network_interface",
        "//software/logger",
        "@boost//:asio",
    ],
)

cc_library(
    name = "threaded_proto_multicast_sender",
    hdrs = [
        "threaded_proto_multicast_sender.h",
        "threaded_proto_multicast_sender.tpp",
    ],
    deps = [
        ":configured_network_interface",
        ":proto_multicast_sender",
        "@boost//:asio",
    ],
)
