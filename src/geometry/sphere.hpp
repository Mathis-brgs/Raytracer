#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/ray.hpp"
#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/vector.hpp"

class Sphere : public Shape {
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
    std::optional<HitInfo> intersect(const Ray& ray) const override;
};
