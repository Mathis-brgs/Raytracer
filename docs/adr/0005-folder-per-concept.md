# 0005 — One folder per concept

## Status

Accepted

## Context

All our code sat in one flat `src/` folder, and all our tests in one flat `tests/` folder. That is fine for two or three classes. A ray tracer will have many: vectors, rays, shapes, materials, cameras, images. In one folder, they are hard to tell apart, and it is not clear which test file belongs to which class.

We want to find a class, and its tests, from its concept. We want to do it now, while there is only one class to move.

## Decision

Each concept gets its own folder under `src/`, with its headers and sources. For example, `Vector` lives in `src/math/vector.hpp` and `src/math/vector.cpp`.

The tests mirror this layout: the tests for `src/math/vector.cpp` live in `tests/math/vector_test.cpp`.

Includes always start from `src/`, for example `#include "math/vector.hpp"`.

## Consequences

- A class, and its tests, are found from the folder of their concept.
- An include line shows where a header comes from.
- Moving a file means changing `CMakeLists.txt`, the includes that name it and its test.
- Someone must decide which concept a class belongs to, and a folder with one file can look like overkill at first.
- Nothing separates the public parts of a folder from its private parts.

## Left out for now

- **Namespaces**, such as `raytracer::Vector`. Worth it when two classes want the same name, or when other studios use our code inside theirs.
- **One library per folder.** Worth it when we want the build to stop one folder from depending on another, or when build times grow.
- **A separate `include/` folder** for public headers. Worth it when we ship the ray tracer as a library and must say which headers are public.
