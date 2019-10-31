# Description:
#   Runs the cubemx installer to get the CubeMX binary which can
#   be used by other tools as the genrule is flagged as executable
#
package(default_visibility = ["//visibility:public"])

genrule(
    name = "generate_cubemx_binary",
    outs = ["STM32CubeMX"],
    srcs = [
        "SetupSTM32CubeMX-5.4.0.linux",
        "SetupSTM32CubeMX-5.4.0.exe",
        "auto-install.xml"
    ],
    executable = True,
    # TODO ask gareth, why can't I access .linux in the same dir as auto-install.xml
    cmd = "\n".join([
        # supress both stdout and stderr
        "external/cubemx/SetupSTM32CubeMX-5.4.0.linux auto-install.xml",#> /dev/null 2> /dev/null",
        # copy the generated header to the location bazel expects it
        "mv external/cubemx/STM32CubeMX/STM32CubeMX $@",
    ]),
)
