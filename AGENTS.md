# Agent instructions

## Build, run and test

```sh
make        # build
make run    # build and run
make test   # build and run all tests
make clean  # delete the build directory
```

These wrap CMake and CTest. See `Makefile` at the root for the full commands.

## Contributing

Contributor rules (dev container set-up, TDD, ADR process, pull requests) are in `CONTRIBUTING.md`. Pull requests and issues use the templates in `.github/`. The CI (`.github/workflows/ci.yml`) runs `make test` in the dev container image on every pull request; keep it working when you change the build.

## Code style

- Every private member variable starts with an underscore: `_x`, not `x`. Constructor parameters keep the plain name (`Vector(double x, ...) : _x(x)`).
- No `get` prefix on getters: it is redundant. Write `v.x()`, not `v.getX()`.

## How we work

- Test-driven development: write a failing test first, then only enough code to make it pass.
- Expected values in tests come from the maths, not from running the code. If a test fails, ask me before changing what it expects.
- One small step at a time. Do only what I ask for, nothing more.
- Keep the C++ simple. No advanced features unless I ask for them.
- Do not build or run anything on the host. The commands above run in the dev container.

## Source layout

New classes go in the folder of their concept, under `src/`, and their tests in the matching folder under `tests/`. Includes start from `src/`, for example `#include "math/vector.hpp"`. See `docs/adr/0005-folder-per-concept.md`.

## Architecture decisions

Decisions about the build system, toolchain, test framework, and project structure are recorded in `docs/adr/`. Read the ADRs in that directory before changing the build, the tools, or the test setup.

- Never act against an Accepted ADR. To change a decision, write a new ADR with status **Proposed** and ask the user before proceeding.
- Never set an ADR's status to Accepted yourself. That is the user's decision.
