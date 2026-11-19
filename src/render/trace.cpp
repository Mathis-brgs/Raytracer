#include "render/trace.hpp"

#include <optional>

#include "geometry/hit_info.hpp"

Colour trace(const Ray& ray, const Scene& scene) {
    std::optional<HitInfo> hit = scene.nearestHit(ray);
    if (!hit) {
        return Colour(0, 0, 0); // no hit, nothing to shade
    }
    return hit->material.shade(*hit, scene.light());
}
