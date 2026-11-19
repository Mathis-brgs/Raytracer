# 0007 — Save images as PNG with LodePNG

## Status

Proposed

## Context

The client opens our images in ordinary viewers, so we save them as PNG. PNG is compressed and has a checksum on every block. Writing it ourselves would take days, so we use a library.

We compared four options:

- **libpng.** The reference library. Its C API takes many calls to save one image, and it needs zlib, which is not in our dev container.
- **stb_image_write.** A single header, public domain. A C API with raw pointers, and larger PNG files.
- **LodePNG.** One `.cpp` and one `.h`, zlib licence, no dependencies. A C++ API with `std::vector`. Slower than the others at saving.
- **PPM, written by hand.** No library, but most viewers cannot open it, and the files are far bigger.

## Decision

We save images with LodePNG (https://github.com/lvandeve/lodepng). CMake downloads it with `FetchContent`, like Catch2. LodePNG has no releases, so we pin one commit: `7b2893e35891c0c85bee5595caafaf3c2044b409`.

Only `src/io/png_saver.cpp` uses LodePNG. It sits behind our own interface, `ImageSaver`, with one method: `save(image, path)`. `raytracer_core` links LodePNG as `PRIVATE`, so the rest of the code cannot include it.

## Consequences

- The client can open our images in any viewer.
- Nothing is added to the dev container: CMake downloads LodePNG.
- The first configure needs internet access, in the container and in CI, as for Catch2.
- Upgrading LodePNG means changing the pinned commit on purpose.
- Saving is slower than with the other libraries. We accept it for the simple C++ API.
- A new library or format, such as EXR for film studios, is one new class behind `ImageSaver`. The code that saves does not change.
- `ImageSaver` is one more layer, and for now it has a single implementation.
- The zlib licence asks us to keep its notice in LodePNG's source. A mention in our documentation is welcome but not required.
