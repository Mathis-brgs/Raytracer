#pragma once

#include "math/vector.hpp"

class Camera {
private:
    Vector _eye;
    int _width;
    int _height;

public:
    Camera(const Vector& eye, int width, int height);

    Vector eye() const;
    int width() const;
    int height() const;
};
