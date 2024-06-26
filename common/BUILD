load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "headers",
    hdrs = [
        "bit_slice.h",
        "compatibility.h",
        "tools_utils.h",
        "tools_version.h",
    ],
    include_prefix = "common",
)

cc_library(
    name = "filesystem",
    srcs = [
        "tools_filesystem.cpp",
    ],
    hdrs = [
        "tools_filesystem.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
)

cc_binary(
    name = "tools-filesystem-test-bin",
    srcs = [
        "tools_filesystem_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":filesystem",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "boost-filesystem-test-bin",
    srcs = [
        "tools_filesystem_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    defines = ["USE_BOOST"],
    deps = [
        ":filesystem",
        "@boost//:filesystem",
        "@com_google_googletest//:gtest_main",
    ],
)

sh_test(
    name = "tools-filesystem-test",
    size = "small",
    srcs = [
        "tools_filesystem_test.sh",
    ],
    args = ["tools-filesystem-test-bin"],
    data = [
        ":tools-filesystem-test-bin",
    ],
)

sh_test(
    name = "boost-filesystem-test",
    size = "small",
    srcs = [
        "tools_filesystem_test.sh",
    ],
    args = ["boost-filesystem-test-bin"],
    data = [
        ":boost-filesystem-test-bin",
    ],
)

cc_library(
    name = "algorithm",
    srcs = [
        #
    ],
    hdrs = [
        "tools_algorithm.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        #
    ],
)

cc_library(
    name = "boost-algorithm",
    srcs = [
        #
    ],
    hdrs = [
        "tools_algorithm.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    defines = ["USE_BOOST_ALGORITHM"],
    deps = [
        "@boost//:algorithm",
    ],
)

cc_test(
    name = "tools-algorithm-test",
    size = "small",
    srcs = [
        "tools_algorithm_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":algorithm",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "boost-algorithm-test",
    size = "small",
    srcs = [
        "tools_algorithm_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":boost-algorithm",
        "@com_google_googletest//:gtest_main",
    ],
)

genrule(
    name = "gen-config-h",
    outs = ["config.h"],
    cmd = "touch $@",
)

cc_library(
    name = "config-h",
    hdrs = [
        ":gen-config-h",
    ],
    include_prefix = ".",
)

cc_library(
    name = "regex",
    srcs = [
        "tools_regex.cpp",
    ],
    hdrs = [
        "tools_regex.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":config-h",
    ],
)

cc_library(
    name = "stdlib-regex",
    srcs = [
        "tools_regex.cpp",
    ],
    hdrs = [
        "tools_regex.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    defines = ["USE_STDLIB_REGEX"],
    deps = [
        ":config-h",
    ],
)

cc_library(
    name = "boost-regex",
    srcs = [
        "tools_regex.cpp",
    ],
    hdrs = [
        "tools_regex.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    defines = ["USE_BOOST_REGEX"],
    deps = [
        ":config-h",
        "@boost//:regex",
    ],
)

cc_test(
    name = "tools-regex-test",
    size = "small",
    srcs = [
        "tools_regex_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":regex",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "stdlib-regex-test",
    size = "small",
    srcs = [
        "tools_regex_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":stdlib-regex",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "boost-regex-test",
    size = "small",
    srcs = [
        "tools_regex_test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        ":boost-regex",
        "@com_google_googletest//:gtest_main",
    ],
)
