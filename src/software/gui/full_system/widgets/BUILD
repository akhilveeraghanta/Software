load("@bazel_rules_qt//:qt.bzl", "qt_cc_library")

package(default_visibility = ["//software/gui:__subpackages__"])

qt_cc_library(
    name = "full_system_gui",
    src = "full_system_gui.cpp",
    hdr = "full_system_gui.h",
    deps = [
        ":ai_control",
        "//software/ai/hl/stp:play_info",
        "//software/gui:geometry_conversion",
        "//software/gui/full_system/ui:main_widget",
        "//software/gui/generic_widgets/robot_status",
        "//software/multithreading:thread_safe_buffer",
        "//software/proto:sensor_msg_cc_proto",
        "//software/time:duration",
        "@qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "ai_control",
    src = "ai_control.cpp",
    hdr = "ai_control.h",
    deps = [
        "//software/ai/hl/stp/play",
        "//software/gui/full_system/ui:main_widget",
        "//software/gui/shared:parameters_spinbox",
        "//software/parameter:dynamic_parameters",
        "//software/util/design_patterns:generic_factory",
        "@qt//:qt_widgets",
    ],
)
