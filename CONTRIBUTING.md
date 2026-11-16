# Contributing

Thank you for helping. Please read the [code of conduct](CODE_OF_CONDUCT.md) first.

## Set up

1. Install [Docker](https://docs.docker.com/get-docker/) and [VS Code](https://code.visualstudio.com/) with the Dev Containers extension.
2. Open the project folder in VS Code, then run **Dev Containers: Reopen in Container**.
3. Work in the VS Code terminal. The container has the same toolchain as the CI.

## Commands

```
make        # build
make run    # build and run
make test   # build and run all tests
make clean  # delete the build directory
```

## How we work: TDD

1. **Red:** write a test in `tests/` for behaviour that does not exist yet. It must fail.
2. **Green:** write the simplest code in `src/` that makes it pass.
3. **Refactor:** clean up. The tests must stay green.

A new test file must be listed in `add_executable(raytracer_tests ...)` in `CMakeLists.txt`.

## Decisions: ADRs

Our decisions are in [docs/adr/](docs/adr/). Read them before you change the build, the tools or the test setup.

- Do not go against an accepted ADR.
- To change a decision, add a new ADR with status **Proposed**, in the same format (Title, Context, Decision, Status, Consequences). Number it next in the list.
- A maintainer accepts it. Do not set an ADR to Accepted yourself.

## Submit a change

1. Open an [issue](../../issues) first for anything large.
2. Make your change with tests. Run `make test`.
3. Open a pull request and fill in the template. The CI must pass.
