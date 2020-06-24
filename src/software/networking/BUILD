package(default_visibility = ["//visibility:public"])

genrule(
        name = "configured_network_interface",
        outs = ["configured_network_interface.h"],
        cmd = "\n".join([
            # we load the TBOTS_WIFI_INTERFACE env variable that is configured through `setup_networking.sh`
            # and bring that into a header as a const string. networking libraries that need the configued
            # interface will include this header and will have access to the configured string
            "echo \'#pragma once const std::string CONFIGURED_NETIF = \"\' > pre_out.h",
            "echo $$TBOTS_WIFI_INTERFACE >> pre_out.h",
            "echo \'\";\' >> pre_out.h",

            # we truncate the new line characters, because its easier to 
            "tr -d \'\n\' < pre_out.h >> out.h",
            "mv out.h $@",
        ]),
        local = True,
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
        "configured_network_interface.h",
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
        "configured_network_interface.h",
    ],
    deps = [
        ":proto_multicast_sender",
        "@boost//:asio",
    ],
)
