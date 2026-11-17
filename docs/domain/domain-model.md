```mermaid
classDiagram
    Camera "1" --> "*" Ray : sends
    class Ray {
        origin: Vector
        direction: Vector
    }
```
