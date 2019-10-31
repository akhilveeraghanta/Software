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

py_binary(
    name = "regen",
    srcs = ["regen.py"],
    restricted_to = ["//cc_toolchain:stm32h7"],
    deps = ["@rules_python//python/runfiles"],
    data = ["@cubemx//:STM32CubeMX",],
)
