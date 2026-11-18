#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "shapes/sphere.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

TEST_CASE("a ray aimed at the centre hits the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));
    REQUIRE(sphere.hits(ray));
}

TEST_CASE("a ray passing above the sphere misses it", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 2, -5), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.hits(ray));
}



