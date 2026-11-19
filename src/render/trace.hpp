#pragma once

#include "colour/colour.hpp"
#include "geometry/ray.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"

// The colour a ray sees: what the material shades where it hits the sphere, under the light.
// Black if it misses.
Colour trace(const Ray& ray, const Sphere& sphere, const Light& light);
