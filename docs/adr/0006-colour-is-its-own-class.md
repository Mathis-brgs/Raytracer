# 0006 — Colour is its own class

## Status

Accepted

## Context

A colour is three numbers: red, green and blue. A `Vector` is also three numbers. We could reuse `Vector` for colours and get its operations for free.

But the two mean different things. Adding a colour to a point, or taking the dot product of two colours, makes no sense. With one class, the compiler cannot stop these mistakes. The names would also be wrong: `colour.x()` for red does not read like the client's words.

## Decision

`Colour` is its own class, in `src/colour/`. It holds `r`, `g` and `b`, each from 0 to 1, with a constructor and getters. It gets an operation only when a test needs it.

## Consequences

- The compiler refuses a `Colour` where a `Vector` is expected, and the reverse.
- The code reads like the domain: `colour.r()`, not `colour.x()`.
- Operations we need on both, such as scaling or adding, are written twice.
- Values are not checked: a colour can still be given 2 or -1.
