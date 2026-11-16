# 0001 — Dev Container

## Status

Proposed

## Context

The team works on macOS, Linux, and Windows. Without a shared environment, each contributor installs the toolchain independently and builds can silently diverge.

Alternatives considered:
- **Local install** — simple, but compiler and CMake versions differ per machine.
- **Docker Compose** — solves reproducibility but requires more configuration and does not integrate with VS Code out of the box.
- **GitHub Codespaces** — cloud-hosted Dev Containers; works but requires a network connection and a Codespaces subscription.

## Decision

Use a Dev Container (`.devcontainer/`) with a pinned Ubuntu 24.04 image. The container fixes GCC 13.3, CMake 3.28, and Ninja. VS Code opens the project inside the container automatically.

## Consequences

- Every contributor gets an identical environment regardless of host OS.
- Builds and test results are reproducible.
- Contributors must install Docker and VS Code (or the `devcontainer` CLI). Docker is a non-trivial dependency on Windows.
- The image must be updated deliberately when toolchain versions need to change.
