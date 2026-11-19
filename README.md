# Raytracer

A ray tracer written in C++, built to be readable, tested, documented and open to contributions.

## Status

The ray tracer renders one red sphere and saves it as a PNG file. The camera sends one ray through the centre of every pixel. Lighting, a floor and shadows come next.

## Documentation

- [Discovery report](docs/discovery/discovery-report.md): problem statement, client interview summary, state of the art, and first notes on ray tracing and C++.
- [Domain model](docs/domain/domain-model.md): the classes and the client's words.
- [Pinhole spike](docs/spikes/pinhole-spike.md): the first ray, from the eye to one pixel.
- [Architecture decisions](docs/adr/): one ADR per decision (dev container, CMake, Catch2, CI, folders, colour, PNG output, coordinates).
- [Contributing](CONTRIBUTING.md): set-up, commands, TDD, ADRs and how to submit a change.
- [Code of conduct](CODE_OF_CONDUCT.md).

## Build environment

Everyone builds in the same Docker container, on macOS, Linux and Windows. It fixes the toolchain: Ubuntu 24.04, GCC 13.3, CMake 3.28, Ninja. Tests use Catch2 3.7.1.

1. Install [Docker](https://docs.docker.com/get-docker/) and [VS Code](https://code.visualstudio.com/) with the Dev Containers extension.
2. Open the project folder in VS Code, then run **Dev Containers: Reopen in Container**.
3. Use the terminal inside VS Code for the commands below.

Zed and the `devcontainer` CLI also read [.devcontainer/devcontainer.json](.devcontainer/devcontainer.json).

## Build and run

```
make        # build
make run    # build and run
make clean  # delete the build directory
```

Expected output: `image.png`. The program writes `image.png` at the root of the project: a red disc on black, 400 × 300. The file is ignored by git.

The first build downloads Catch2 and [LodePNG](https://github.com/lvandeve/lodepng), so it needs internet access.

## Tests and TDD

Tests use [Catch2](https://github.com/catchorg/Catch2) and are run by CTest.

```
make test
```

TDD loop for each new feature:

1. **Red:** write a test in `tests/` for behaviour that does not exist yet. Build and run: it fails.
2. **Green:** write the simplest code in `src/` that makes it pass.
3. **Refactor:** clean up the code. The tests must stay green.

Example: [tests/geometry/sphere_test.cpp](tests/geometry/sphere_test.cpp) tests `Sphere` from [src/geometry/sphere.cpp](src/geometry/sphere.cpp).

Useful Catch2 macros:

| Macro | Purpose |
|---|---|
| `REQUIRE(expr)` | Check; stop the test on failure |
| `CHECK(expr)` | Check; continue the test on failure |
| `REQUIRE_THROWS(expr)` | Expect an exception |
| `Catch::Approx(x).epsilon(e)` | Compare floating-point numbers with a margin ([example](tests/float_test.cpp)) |

## Adding files

Each concept has its own folder (see [ADR 0005](docs/adr/0005-folder-per-concept.md)). Includes start from `src/`, for example `#include "math/vector.hpp"`.

1. Create `src/concept/yourfile.cpp` and `src/concept/yourfile.hpp`, and add the `.cpp` to `add_library(raytracer_core ...)` in [CMakeLists.txt](CMakeLists.txt).
2. Create `tests/concept/yourfile_test.cpp`, and add it to `add_executable(raytracer_tests ...)` in the same file.

## Project layout

```
.devcontainer/   Docker environment
.github/         CI workflow, pull request and issue templates
docs/            Discovery report, domain model, spike notes and ADRs
src/             Library code, one folder per concept, and main.cpp
tests/           Tests, in the same folders as src/
CMakeLists.txt   Build definition
Makefile         Shortcuts: build, run, test, clean
```

## Licence

[MIT](LICENSE).
