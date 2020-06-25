package(default_visibility = ["//visibility:public"])

genrule(
    name = "gen_configured_network_interface",
    outs = ["configured_network_interface.h"],
    cmd = "\n".join([

        # we load the TBOTS_WIFI_INTERFACE env variable that is configured through `setup_networking.sh`
        # and bring that into a header as a const string. Libraries that need the user configued
        # interface will include this header and will have access to the interface string
        "echo \'#pragma once\' > out.h",
        "echo -e 'const std::string CONFIGURED_NETWORK_INTERFACE = \"\\c' >> out.h",
        "echo -e $$TBOTS_WIFI_INTERFACE\\\\c >> out.h",
        "echo -e '\";\\c' >> out.h",
        "mv out.h $@",
    ]),
    visibility = ["//visibility:private"],
)

cc_library(
    name = "configured_network_interface",
    hdrs = [
        "configured_network_interface.h",
    ],
)

cc_library(
    name = "proto_multicast_listener",
    hdrs = [
        "proto_multicast_listener.h",
        "proto_multicast_listener.tpp",
    ],
    visibility = ["//visibility:private"],
    deps = [
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
        ":proto_multicast_sender",
        "@boost//:asio",
    ],
)
