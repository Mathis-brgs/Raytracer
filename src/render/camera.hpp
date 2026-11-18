#pragma once

#include "math/vector.hpp"

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
};
