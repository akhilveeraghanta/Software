package(default_visibility = ["//visibility:public"])

genrule(
    name = "configured_network_interface",
    outs = ["configured_network_interface.h"],
    cmd = "\n".join([

        # we load the TBOTS_WIFI_INTERFACE env variable that is configured through `setup_networking.sh`
        # and bring that into a header as a const string. Libraries that need the user configued
        # interface will include this header and will have access to the interface string
        "echo \'#pragma once const std::string CONFIGURED_NETWORK_INTERFACE = \"\' > pre_out.h",
        "echo $$TBOTS_WIFI_INTERFACE >> pre_out.h",
        "echo \'\";\' >> pre_out.h",

        # we truncate the new line characters to bring everything into one line
        # this is easier than trying to format everything in one line in the first place
        "tr -d \'\n\' < pre_out.h >> out.h",
        "mv out.h $@",
    ]),
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
        "configured_network_interface.h",
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
        "configured_network_interface.h",
        "threaded_proto_multicast_sender.h",
        "threaded_proto_multicast_sender.tpp",
    ],
    deps = [
        ":proto_multicast_sender",
        "@boost//:asio",
    ],
)
