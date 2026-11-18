#pragma once

#include "math/vector.hpp"
#include "ray/ray.hpp"

class Sphere {
private:
    Vector _centre;
    double _radius;

public:
    Sphere(const Vector& centre, double radius);

    Vector centre() const;
    double radius() const;

    bool hits(const Ray& ray) const;
    Vector hitPoint(const Ray& ray) const;
};
