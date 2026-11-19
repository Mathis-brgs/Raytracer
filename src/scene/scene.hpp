#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit_info.hpp"
#include "geometry/ray.hpp"
#include "geometry/shape.hpp"
#include "light/light.hpp"

// Everything the camera looks at: the shapes and the light.
class Scene {
private:
    Light _light;
    // unique_ptr: the scene owns its shapes, and deletes them when it goes.
    // A pointer, not a Shape, because each shape is a different subclass.
    std::vector<std::unique_ptr<Shape>> _shapes;

public:
    Scene(const Light& light);

    const Light& light() const;

    // Takes the shape over: call it as add(std::make_unique<Sphere>(...)).
    void add(std::unique_ptr<Shape> shape);

    // Of all the shapes the ray hits, the nearest one (smallest t), or nothing.
    std::optional<HitInfo> nearestHit(const Ray& ray) const;
};
