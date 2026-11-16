# 0002 — CMake and CTest

## Status

Accepted

## Context

The project needs a build system for a C++ codebase that will grow across milestones and must be accessible to partner studios.

Alternatives considered:
- **Make** — ubiquitous but requires hand-written rules; poor cross-platform support.
- **Meson** — modern and readable, but less known in the C++ film-industry ecosystem.
- **Bazel** — powerful for large monorepos; steep learning curve for a small project.
- **xmake** — lightweight; very low adoption outside the gaming community.

## Decision

Use CMake 3.28 as the build system with CTest as the test runner. `FetchContent` pins third-party dependencies (Catch2) at exact versions without an external package manager.

A small root `Makefile` gives short commands (`make`, `make run`, `make test`, `make clean`). It only calls CMake and CTest. CMake still defines and performs the build.

## Consequences

- CMake is the de-facto standard in C++ open-source and in studios; partners and contributors already know it.
- CTest is bundled with CMake, so no extra tool is needed to discover and run tests.
- CMake's syntax (CMakeLists.txt) is verbose and historically inconsistent; newcomers often find it hard to read.
- `FetchContent` downloads dependencies at configure time, which requires a network connection on first build.
