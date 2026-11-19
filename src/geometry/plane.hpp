#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/ray.hpp"
#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/vector.hpp"

// A flat surface with no edges, such as a floor. Given by one point on it and its normal.
class Plane : public Shape {
private:
    Vector _point;
    Vector _normal; // length 1
    std::shared_ptr<const Material> _material;

public:
    // The normal does not need length 1: the plane normalises it.
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    std::optional<HitInfo> intersect(const Ray& ray) const override;
};
