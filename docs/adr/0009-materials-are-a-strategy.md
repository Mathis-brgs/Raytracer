# 0009 — Materials are a Strategy

## Status

Proposed

## Context

A sphere held a `Colour`, and `trace` returned it on a hit. The client wants diffuse light, reflection and shadows, so the colour a ray sees will soon depend on more than one fixed colour. Each surface may be computed in a different way.

If `trace` held every way of colouring a surface, it would grow with each new kind, and each change could break the others.

## Decision

A surface's colour comes from its material. `Material`, in `src/material/`, is an abstract class with one function: `shade()`, which returns a `Colour`. Each kind of material is a subclass. This is the Strategy pattern, as for `ImageSaver`.

The first subclass is `FlatMaterial`: it returns its colour, with no light.

A `Sphere` keeps its material in a `std::shared_ptr<const Material>`, so several spheres can share one. `trace` returns `sphere.material().shade()` on a hit.

`trace` stays outside `Sphere`. Soon it will have to find the nearest of several objects and handle lights. That is about the whole scene, not one sphere.

## Consequences

- A new kind of material is one new class. `Sphere` and `trace` do not change.
- `shade()` takes nothing yet. With light, it will need the hit point, the normal and the light, and every subclass will change then.
- `shared_ptr` is one more C++ idea to learn. A plain reference would be simpler, but it could point to a material that no longer exists.
- Each call to `shade()` goes through a virtual function. The cost is small next to the hit test.
