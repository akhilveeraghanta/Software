load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "ssl_proto",
    srcs = [
        "ssl_gc_api.proto",
        "ssl_gc_change.proto",
        "ssl_gc_ci.proto",
        "ssl_gc_common.proto",
        "ssl_gc_game_event.proto",
        "ssl_gc_geometry.proto",
        "ssl_gc_referee_message.proto",
        "ssl_gc_engine.proto",
        "ssl_gc_state.proto",
        "ssl_gc_engine_config.proto",
        "ssl_vision_detection.proto",
        "ssl_vision_detection_tracked.proto",
        "ssl_vision_geometry.proto",
        "ssl_vision_wrapper.proto",
        "ssl_vision_wrapper_tracked.proto",
    ],
    deps = [
        "@com_github_protocolbuffers_protobuf//:duration_proto",
        "@com_github_protocolbuffers_protobuf//:timestamp_proto",
    ],
    visibility = ["//visibility:private"],
)

proto_library(
    name = "sensor_msg_proto",
    srcs = [
        "sensor_msg.proto",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":ssl_proto",
        "//shared/proto:tbots_proto",
    ],
)

proto_library(
    name = "replay_msg_proto",
    srcs = [
        "replay_msg.proto",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":sensor_msg_proto",
        ":ssl_proto",
        "//shared/proto:tbots_proto",
    ],
)

cc_proto_library(
    name = "ssl_cc_proto",
    deps = [":ssl_proto"],
)

cc_proto_library(
    name = "sensor_msg_cc_proto",
    deps = [":sensor_msg_proto"],
)

cc_proto_library(
    name = "replay_msg_cc_proto",
    deps = [":replay_msg_proto"],
)
