#include "scene/scene.hpp"

#include <utility>

Scene::Scene(const Light& light)
    : _light(light) {}

const Light& Scene::light() const { return _light; }

// std::move: a unique_ptr cannot be copied, only handed over.
void Scene::add(std::unique_ptr<Shape> shape) { _shapes.push_back(std::move(shape)); }

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<HitInfo> hit = shape->intersect(ray);
        if (hit && (!nearest || hit->t < nearest->t)) {
            // emplace, not =: HitInfo holds a reference (the material), and a reference
            // cannot be reassigned. emplace builds a new HitInfo in place instead.
            nearest.emplace(*hit);
        }
    }
    return nearest;
}
