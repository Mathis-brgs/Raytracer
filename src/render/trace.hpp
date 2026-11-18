#pragma once

#include "colour/colour.hpp"
#include "geometry/ray.hpp"
#include "geometry/sphere.hpp"

// The colour a ray sees: the sphere's colour if it hits it, black if not.
Colour trace(const Ray& ray, const Sphere& sphere);
