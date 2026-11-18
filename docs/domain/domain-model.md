# Domain model


## Diagram

```mermaid
classDiagram
    Camera "1" --> "*" Ray : sends, one per pixel
    Ray "*" --> "*" Sphere : hits

    class Camera {
        eye: Vector
        width: int
        height: int
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
| Camera | The eye, where rays start, and a screen of `width` × `height` pixels in front of it. |
| Ray | A half-line: a starting point and a direction. The point at distance `t` is `origin + t × direction`. |
| Sphere | A ball, given by its centre and its radius. |
| Vector | Three numbers `x`, `y`, `z`. Used for points and for directions. |
