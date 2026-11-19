#pragma once

#include <memory>

#include "math/vector.hpp"
#include "geometry/ray.hpp"
#include "material/material.hpp"

class Sphere {
private:
    Vector _centre;
    double _radius;
    // Shared: several spheres can use the same material.
    std::shared_ptr<const Material> _material;

public:
    Sphere(const Vector& centre, double radius, std::shared_ptr<const Material> material);

    Vector centre() const;
    double radius() const;
    const Material& material() const;
    // Does the ray hit the sphere in front of its origin?
    bool hits(const Ray& ray) const;
    // The nearest point in front of the ray's origin. Call only when hits(ray) is true.
    Vector hitPoint(const Ray& ray) const;
};
