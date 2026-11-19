# 0008 — Coordinates: x right, y up, z forward

## Status

Proposed

## Context

The camera turns a pixel into a point in the world, so the code needs one agreed way to count. There are two systems:

- **The world.** Points and directions, measured from the centre of the screen.
- **The image.** Pixels, counted from the top left, like text on a page and like every image file.

Ray Tracing in One Weekend uses another choice for the world: the camera looks along −z.

## Decision

- **World:** x goes right, y goes up, z goes forward. The camera looks along +z.
- **Image:** column 0 is on the left, row 0 is at the top. Columns go right, rows go down.
- `rayThroughPixel` turns the row round, so that row 0 is the top of the screen: `y = (height / 2 - row - 0.5) × pixel size`.

We keep the names apart: `column` and `row` for the image, `x`, `y` and `z` for the world. `Camera` already does. `Image` still calls its parameters `x` and `y`, and should be renamed.

## Consequences

- Looking along +z means positive distances in front of the camera, which is easier to read in tests.
- The image order matches the PNG file order, so saving needs no flip.
- The y flip is one more thing to get right. The off-centre camera tests catch it.
- Code or examples from Ray Tracing in One Weekend need their z sign changed.
- The camera cannot turn yet. Pointing it elsewhere needs more vector maths and a new decision.
