#pragma once

#include "geometry/ray.hpp"
#include "math/vector.hpp"

// For now, the camera always looks along +z.
class Camera {
private:
    Vector _eye;
    int _width;
    int _height;
    double _distance;

public:
    Camera(const Vector& eye, int width, int height, double distance);

    Vector eye() const;
    int width() const;
    int height() const;
    double distance() const;

    Ray rayThroughCentre() const;
};
