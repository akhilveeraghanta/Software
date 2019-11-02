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


# Tool to help generate the code frmo the ioc file
#
# The following genrule/binary chain will perform the following:
#   [our code] -> [cubemx folder structure] -> [cubemx] -> [generated_code] -> [our code]

# grab the files we need from our src/headers and
# create Src Hdrs
filegroup(
    name = "firmware_srcs",
    srcs = glob(["firmware_new/boards/frankie_v1/*.c",]),
)

filegroup(
    name = "firmware_hdrs",
    srcs = glob(["firmware_new/boards/frankie_v1/*.h",]),
)

genrule(
    name = "cubemx_folder_structure_generate",
    srcs = [
        ":firmware_srcs",
        ":firmware_hdrs",
    ],
    outs = [
    ],
    cmd = "python3 firmware_new/tools/regen.py\
           $(srcs)",
    visibility = ["//visibility:private"],
)

py_binary(
    name = "regen",
    srcs = ["regen.py"],
    restricted_to = ["//cc_toolchain:stm32h7"],
    deps = ["@rules_python//python/runfiles"],
    data = ["@cubemx//:STM32CubeMX",],
)
