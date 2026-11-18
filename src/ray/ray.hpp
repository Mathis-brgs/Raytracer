#pragma once

#include "math/vector.hpp"

class Ray {
private:
    Vector _origin;
    Vector _direction;

public:
    Ray(const Vector& origin, const Vector& direction);

    Vector origin() const;
    Vector direction() const;

    Vector at(double t) const;
};
