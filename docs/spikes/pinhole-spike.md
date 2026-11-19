# Pinhole spike

## Question

Do the classes of our domain model fit together to give the colour of one pixel?

## Answer

Yes. A camera sends a ray from its eye through the centre of the screen. The sphere says if the ray hits it. If it does, the pixel takes the sphere's colour; if not, it is black. With the eye at (0, 0, -1) and a red sphere at (0, 0, 9), radius 5, `make run` prints `(1, 0, 0)`.

## What we learned

- `Colour` is its own class, not a `Vector` ([ADR 0006](../adr/0006-colour-is-its-own-class.md)).
- The colour decision first sat in `main`. It now lives in `trace`, which is tested.
- `Ray` and `Sphere` belong together in `geometry/`; `Camera` and `trace` in `render/`.

## Bugs found

| Bug | How we found it | State |
|---|---|---|
| A sphere behind the eye was hit: the code only checked the discriminant, not `t > 0`. | Test with the sphere at (0, 0, -10). | Fixed |
| A ray starting inside the sphere gave a hit point behind its origin. | Test with the ray starting at the centre. | Fixed |
| Forgetting to square the radius is only caught by an off-centre sphere. | Test with the sphere at (3, 0, 9), checked by breaking the code on purpose. | Covered by a test |

## Left for later

- A ray that only touches the sphere counts as a hit. Not tested.
- `hits` only says yes or no. Later we need "at which `t`", so `hits` and `hitPoint` stop repeating the same maths.
- `trace` takes one concrete `Sphere`. A scene with several shapes will need a common interface.
- The camera only sends the ray through the screen centre. One ray per pixel comes next.
