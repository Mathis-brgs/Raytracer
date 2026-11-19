#pragma once

#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/ray.hpp"

// Anything a ray can hit. Each kind of shape (sphere, plane...) is a subclass.
class Shape {
public:
    virtual ~Shape() = default;
    // The nearest hit in front of the ray's origin, or nothing.
    virtual std::optional<HitInfo> intersect(const Ray& ray) const = 0;
};
