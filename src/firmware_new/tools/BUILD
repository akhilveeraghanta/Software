sh_binary(
    name = "debug_firmware_on_arm_board",
    srcs = ["debug_firmware_on_arm_board.sh"],
    data = [
        "//firmware_new/boards/frankie_v1:frankie_v1_main",
        "@arm_developer_gcc//:gdb",
    ],
    restricted_to = ["//cc_toolchain:stm32h7"],
    deps = ["@bazel_tools//tools/bash/runfiles"],
)

sh_binary(
    name = "cubemx_regen",
    srcs = ["cubemx_regen.sh"],
    deps = ["@bazel_tools//tools/bash/runfiles"],
)

cc_binary(
    name = "send_proto_over_serial",
    srcs = ["send_proto_over_serial.cpp"],
    deps = ["//firmware_new/tools:robot_cc_proto"],
)

# protobuf used to communicate with our robots
proto_library(
    name = "robot_proto",
    srcs = ["robot_msg.proto",],
    deps = [],
)

cc_proto_library(
    name = "robot_cc_proto",
    deps = [":robot_proto"],
)
