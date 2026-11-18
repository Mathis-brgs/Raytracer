#include <catch2/catch_test_macros.hpp>

#include "render/trace.hpp"
#include "test_helpers.hpp"

// The camera ray from the course: from (0, 0, -1) along +z.
// Orange, not red, so the test proves the colour comes from the sphere.
TEST_CASE("a ray that hits the sphere gets the sphere's colour", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0.5, 0));

    requireColoursEqual(trace(ray, sphere), Colour(1, 0.5, 0));
}

// Sphere at (6, 0, 9), radius 5: delta = -44, the ray misses it (see sphere_test.cpp).
TEST_CASE("a ray that misses the sphere gets black", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0.5, 0));

    requireColoursEqual(trace(ray, sphere), Colour(0, 0, 0));
}
