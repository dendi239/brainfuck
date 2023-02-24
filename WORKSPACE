load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/13e135934b0f3bf1b71982e512cbe1cb11f6414f.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-13e135934b0f3bf1b71982e512cbe1cb11f6414f",
    sha256 = "e6f49fa7e1b0f7cb80c797916f6693305a852cf51ab1bd5797061ece3039e212",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()
