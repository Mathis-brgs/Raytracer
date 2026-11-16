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

## Architecture decisions

Decisions about the build system, toolchain, test framework, and project structure are recorded in `docs/adr/`. Read the ADRs in that directory before changing the build, the tools, or the test setup.

- Never act against an Accepted ADR. To change a decision, write a new ADR with status **Proposed** and ask the user before proceeding.
- Never set an ADR's status to Accepted yourself. That is the user's decision.
