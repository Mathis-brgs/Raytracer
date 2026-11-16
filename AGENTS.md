# Agent instructions

## Build, run and test

```sh
# Configure (first time or after CMakeLists.txt changes)
cmake -S . -B build -G Ninja

# Build
cmake --build build

# Run
./build/raytracer

# Test
ctest --test-dir build --output-on-failure
```

## Architecture decisions

Decisions about the build system, toolchain, test framework, and project structure are recorded in `docs/adr/`. Read the ADRs in that directory before changing the build, the tools, or the test setup.

- Never act against an Accepted ADR. To change a decision, write a new ADR with status **Proposed** and ask the user before proceeding.
- Never set an ADR's status to Accepted yourself. That is the user's decision.
