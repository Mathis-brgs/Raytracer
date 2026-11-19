#include "render/trace.hpp"

#include <optional>

#include "geometry/hit_info.hpp"

Colour trace(const Ray& ray, const Sphere& sphere, const Light& light) {
    std::optional<HitInfo> hit = sphere.intersect(ray);
    if (!hit) {
        return Colour(0, 0, 0); // no hit, nothing to shade
    }
    return hit->material.shade(*hit, light);
}
