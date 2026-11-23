#pragma once

#include "colour/colour.hpp"
#include "geometry/ray.hpp"
#include "scene/scene.hpp"

// The colour a ray sees: the nearest shape it hits, shaded by its material under the scene's light.
// Black if it hits nothing.
Colour trace(const Ray& ray, const Scene& scene);
