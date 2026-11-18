# Domain model


## Diagram

```mermaid
classDiagram
    Camera "1" --> "*" Ray : sends, one per pixel
    Ray "*" --> "0..1" Sphere : hits

    class Camera {
        eye: Vector
        width: int
        height: int
        distance: double
    }
    class Ray {
        origin: Vector
        direction: Vector
    }
    class Sphere {
        centre: Vector
        radius: double
    }
```

## Words

| Word | Meaning |
|---|---|
| Camera | The eye, where rays start, and a screen of `width` × `height` pixels, `distance` in front of the eye. |
| Ray | A half-line: a starting point and a direction. The point at distance `t` is `origin + t × direction`. |
| Sphere | A ball, given by its centre and its radius. |
| Vector | Three numbers `x`, `y`, `z`. Used for points and for directions. |
