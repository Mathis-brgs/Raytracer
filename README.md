# Raytracer

A ray tracer written in C++, built to be readable, tested, documented and open to contributions.

## Status

Discovery phase done. Project bootstrap: Hello World and a test setup. No ray tracing code yet.

## Documentation

- [Discovery report](docs/discovery/discovery-report.md): problem statement, client interview summary, state of the art, and first notes on ray tracing and C++.

## Build environment

Everyone builds in the same Docker container, on macOS, Linux and Windows. It fixes the toolchain: Ubuntu 24.04, GCC 13.3, CMake 3.28, Ninja. Tests use Catch2 3.7.1.

1. Install [Docker](https://docs.docker.com/get-docker/) and [VS Code](https://code.visualstudio.com/) with the Dev Containers extension.
2. Open the project folder in VS Code, then run **Dev Containers: Reopen in Container**.
3. Use the terminal inside VS Code for the commands below.

Zed and the `devcontainer` CLI also read [.devcontainer/devcontainer.json](.devcontainer/devcontainer.json).

## Build and run

```
cmake -S . -B build -G Ninja
cmake --build build
./build/raytracer
```

Expected output: `Hello, ray tracer!`

## Tests and TDD

Tests use [Catch2](https://github.com/catchorg/Catch2) and are run by CTest.

```
cmake --build build
ctest --test-dir build --output-on-failure
```

TDD loop for each new feature:

1. **Red:** write a test in `tests/` for behaviour that does not exist yet. Build and run: it fails.
2. **Green:** write the simplest code in `src/` that makes it pass.
3. **Refactor:** clean up the code. The tests must stay green.

Example: [tests/hello_test.cpp](tests/hello_test.cpp) tests `greet` from [src/hello.cpp](src/hello.cpp). To add a test file, list it in `add_executable(raytracer_tests ...)` in [CMakeLists.txt](CMakeLists.txt).

## Project layout

```
.devcontainer/   Docker environment
src/             Library code and the main program
tests/           Tests
CMakeLists.txt   Build definition
```
