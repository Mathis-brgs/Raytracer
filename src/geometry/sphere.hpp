#pragma once

#include "math/vector.hpp"
#include "colour/colour.hpp"
#include "geometry/ray.hpp"

class Sphere {
private:
    Vector _centre;
    double _radius;
    Colour _colour;

public:
    Sphere(const Vector& centre, double radius, const Colour& colour);

    Vector centre() const;
    double radius() const;
    Colour colour() const;
    // Does the ray hit the sphere in front of its origin?
    bool hits(const Ray& ray) const;
    // The nearest point in front of the ray's origin. Call only when hits(ray) is true.
    Vector hitPoint(const Ray& ray) const;
};
