cc_library(
    name = "brainfuck-lib",
    hdrs = [
        "brainfuck.hpp",
        "errors.hpp",
        "interpreter.hpp",
        "io.hpp",
        "marker.hpp",
        "memory.hpp",
        "program-debug.hpp",
        "program.hpp",
        "tree.hpp",
        "utils.hpp",
    ],
    srcs = [
        "tree.cpp",
    ],
)

cc_test(
    name = "absolutely-inappropriate-words-tests",
    deps = [
        ":brainfuck-lib",
    ],
    srcs = [
        "absolutely-inappropriate-words-tests.cpp",
    ],
)

cc_binary(
    name = "brainfuck",
    srcs = [
        "brainfuck.cpp",
    ],
    deps = [
        ":brainfuck-lib",
    ],
)

cc_binary(
    name = "debugger",
    srcs = [
        "io-debug.hpp",
        "memory-debug.hpp",
        "program-debug.hpp",
        "debugger.cpp",
    ],
    deps = [
        ":brainfuck-lib",
    ],
)
