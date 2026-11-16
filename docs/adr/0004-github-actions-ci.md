# 0004 — GitHub Actions for CI

## Status

Accepted

## Context

Outside contributors will send pull requests. Reviewers need proof that the project builds and the tests pass, in the same environment as the dev container ([0001](0001-dev-container.md)). The repository is hosted on GitHub.

Alternatives considered:
- **No CI** — reviewers run the tests by hand; slow and easy to forget.
- **Another CI service (GitLab CI, CircleCI)** — works, but adds a second service for a project already on GitHub.
- **`devcontainers/ci` action** — runs the dev container directly, but adds a third-party dependency.

## Decision

Use GitHub Actions. One workflow (`.github/workflows/ci.yml`) runs on every pull request and on pushes to `main`. It builds the image from `.devcontainer/Dockerfile`, then runs `make test` inside it. The only external action is `actions/checkout`.

## Consequences

- Every pull request is built and tested in the same toolchain as local work.
- No new tool to learn: the CI runs the same `make test` as contributors.
- The project depends on GitHub for CI. Moving host means rewriting one short file.
- The image is rebuilt on every run, which adds time. A cache can be added later.
- `actions/checkout` is pinned to a major version tag, not a commit.
