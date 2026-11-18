#pragma once

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "ray/ray.hpp"

// Red if the ray hits the top half of the sphere, blue for the bottom half,
// green at the centre's height, black if it misses.
Colour colourAt(const Sphere& sphere, const Ray& ray);
