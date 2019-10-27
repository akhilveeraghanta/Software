package(default_visibility = ["//visibility:public"])

genrule(
    name = "generate_cubemx_binary",
    outs = ["STM32CubeMX"],
    srcs = ["SetupSTM32CubeMX-5.4.0.linux"],
    cmd = "\n".join([
        # run the setup script with the auto
        "SetupSTM32CubeMX-5.4.0.linux external/auto-install.xml > /dev/null 2> /dev/null",
        # Copy the generated header to the location bazel expects it
        "mv STM32CubeMX/STM32CubeMX $@",
    ]),
)

sh_binary(
    name = "runcubemx",
    srcs = ["runcubemx.sh"],
    deps = ["STM32CubeMX"],
)
