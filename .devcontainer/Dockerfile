# Same toolchain for everyone, on macOS, Linux and Windows.
# Ubuntu 24.04 fixes the compiler and CMake versions (GCC 13, CMake 3.28).
FROM ubuntu:24.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        gdb \
        git \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*
