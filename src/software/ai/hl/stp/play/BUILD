package(default_visibility = ["//visibility:public"])

# We force linking for all plays so that the static variables required for the
# "factory" design pattern to work are linked in
# https://www.bfilipek.com/2018/02/static-vars-static-lib.html

cc_library(
    name = "corner_kick_play",
    srcs = ["corner_kick_play.cpp"],
    hdrs = ["corner_kick_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:cherry_pick_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:passer_tactic",
        "//software/ai/hl/stp/tactic:receiver_tactic",
        "//software/ai/passing:pass_generator",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
        "//software/world:ball",
    ],
    alwayslink = True,
)

cc_library(
    name = "defense_play",
    srcs = ["defense_play.cpp"],
    hdrs = ["defense_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:enemy_threat",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:crease_defender_tactic",
        "//software/ai/hl/stp/tactic:defense_shadow_enemy_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:shadow_enemy_tactic",
        "//software/ai/hl/stp/tactic:shoot_goal_tactic",
        "//software/ai/hl/stp/tactic:stop_tactic",
        "//software/logger",
        "//software/parameter:dynamic_parameters",
        "//software/util/design_patterns:generic_factory",
        "//software/world:game_state",
        "//software/world:team",
    ],
    alwayslink = True,
)

cc_library(
    name = "enemy_free_kick_play",
    srcs = ["enemy_free_kick_play.cpp"],
    hdrs = ["enemy_free_kick_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:enemy_threat",
        "//software/ai/hl/stp/tactic:crease_defender_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:shadow_enemy_tactic",
        "//software/ai/hl/stp/tactic:shadow_free_kicker_tactic",
        "//software/ai/hl/stp/tactic:stop_tactic",
        "//software/logger",
        "//software/parameter:dynamic_parameters",
        "//software/util/design_patterns:generic_factory",
        "//software/world:game_state",
    ],
    alwayslink = True,
)

cc_library(
    name = "example_play",
    srcs = ["example_play.cpp"],
    hdrs = ["example_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "halt_play",
    srcs = ["halt_play.cpp"],
    hdrs = ["halt_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:stop_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "free_kick_play",
    srcs = ["free_kick_play.cpp"],
    hdrs = ["free_kick_play.h"],
    deps = [
        ":corner_kick_play",
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:enemy_threat",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:cherry_pick_tactic",
        "//software/ai/hl/stp/tactic:chip_tactic",
        "//software/ai/hl/stp/tactic:crease_defender_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:passer_tactic",
        "//software/ai/hl/stp/tactic:receiver_tactic",
        "//software/ai/hl/stp/tactic:shoot_goal_tactic",
        "//software/ai/passing:pass_generator",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
        "//software/world:ball",
    ],
    alwayslink = True,
)

cc_library(
    name = "kickoff_enemy_play",
    srcs = ["kickoff_enemy_play.cpp"],
    hdrs = ["kickoff_enemy_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:enemy_threat",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:shadow_enemy_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "kickoff_friendly_play",
    srcs = ["kickoff_friendly_play.cpp"],
    hdrs = ["kickoff_friendly_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:kickoff_chip_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "penalty_kick_enemy_play",
    srcs = ["penalty_kick_enemy_play.cpp"],
    hdrs = ["penalty_kick_enemy_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "penalty_kick_play",
    srcs = ["penalty_kick_play.cpp"],
    hdrs = ["penalty_kick_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:penalty_kick_tactic",
        "//software/ai/hl/stp/tactic:penalty_setup_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "shoot_or_chip_play",
    srcs = ["shoot_or_chip_play.cpp"],
    hdrs = ["shoot_or_chip_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:enemy_threat",
        "//software/ai/evaluation:find_open_areas",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:crease_defender_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:shadow_enemy_tactic",
        "//software/ai/hl/stp/tactic:shoot_goal_tactic",
        "//software/ai/hl/stp/tactic:stop_tactic",
        "//software/logger",
        "//software/parameter:dynamic_parameters",
        "//software/util/design_patterns:generic_factory",
        "//software/world:game_state",
    ],
    alwayslink = True,
)

cc_library(
    name = "shoot_or_pass_play",
    srcs = ["shoot_or_pass_play.cpp"],
    hdrs = ["shoot_or_pass_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/evaluation:calc_best_shot",
        "//software/ai/evaluation:possession",
        "//software/ai/hl/stp/tactic:cherry_pick_tactic",
        "//software/ai/hl/stp/tactic:crease_defender_tactic",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/ai/hl/stp/tactic:passer_tactic",
        "//software/ai/hl/stp/tactic:receiver_tactic",
        "//software/ai/hl/stp/tactic:shadow_enemy_tactic",
        "//software/ai/hl/stp/tactic:shoot_goal_tactic",
        "//software/ai/passing:pass_generator",
        "//software/logger",
        "//software/parameter:dynamic_parameters",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "stop_play",
    srcs = ["stop_play.cpp"],
    hdrs = ["stop_play.h"],
    deps = [
        ":play",
        "//shared:constants",
        "//software/ai/hl/stp/tactic:goalie_tactic",
        "//software/ai/hl/stp/tactic:move_tactic",
        "//software/logger",
        "//software/util/design_patterns:generic_factory",
    ],
    alwayslink = True,
)

cc_library(
    name = "play",
    srcs = ["play.cpp"],
    hdrs = ["play.h"],
    deps = [
        "//software/ai/hl/stp/tactic",
        "@boost//:coroutine2",
    ],
)

cc_library(
    name = "all_plays",
    deps = [
        ":corner_kick_play",
        ":defense_play",
        ":enemy_free_kick_play",
        ":example_play",
        ":free_kick_play",
        ":halt_play",
        ":kickoff_enemy_play",
        ":kickoff_friendly_play",
        ":penalty_kick_enemy_play",
        ":penalty_kick_play",
        ":shoot_or_chip_play",
        ":shoot_or_pass_play",
        ":stop_play",
    ],
)

cc_test(
    name = "example_play_test",
    srcs = ["example_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:example_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "kickoff_friendly_play_test",
    srcs = ["kickoff_friendly_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:kickoff_friendly_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "kickoff_enemy_play_test",
    srcs = ["kickoff_enemy_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:kickoff_enemy_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "corner_kick_play_test",
    srcs = ["corner_kick_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:corner_kick_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/simulated_tests/validation_functions",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "defense_play_test",
    srcs = ["defense_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:defense_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "enemy_free_kick_play_test",
    srcs = ["enemy_free_kick_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:enemy_free_kick_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "stop_play_test",
    srcs = ["stop_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:stop_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "halt_play_test",
    srcs = ["halt_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:halt_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "free_kick_play_test",
    srcs = ["free_kick_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:free_kick_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "shoot_or_pass_play_test",
    srcs = ["shoot_or_pass_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:shoot_or_pass_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "shoot_or_chip_play_test",
    srcs = ["shoot_or_chip_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:shoot_or_chip_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "penalty_kick_play_test",
    srcs = ["penalty_kick_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:penalty_kick_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)

cc_test(
    name = "penalty_kick_enemy_play_test",
    srcs = ["penalty_kick_enemy_play_test.cpp"],
    deps = [
        "//software/ai/hl/stp/play:penalty_kick_enemy_play",
        "//software/simulated_tests:simulated_play_test_fixture",
        "//software/simulated_tests:simulated_test_main",
        "//software/simulated_tests/validation:validation_function",
        "//software/test_util",
        "//software/time:duration",
        "//software/world",
    ],
)
