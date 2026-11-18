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

TEST_CASE("a ray aimed at the centre hits the front of the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));

    Vector p = sphere.hitPoint(ray);

    REQUIRE_THAT(p.x(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.y(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.z(), WithinAbs(-1, tolerance));
}

TEST_CASE("a ray off the centre hits the sphere on its curve", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 0.6, -5), Vector(0, 0, 1));

    Vector p = sphere.hitPoint(ray);

    REQUIRE_THAT(p.x(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.y(), WithinAbs(0.6, tolerance));
    REQUIRE_THAT(p.z(), WithinAbs(-0.8, tolerance));
}

TEST_CASE("the hit point follows the sphere when it moves", "[sphere]") {
    Sphere sphere(Vector(0, 0, 10), 2);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    Vector p = sphere.hitPoint(ray);

    REQUIRE_THAT(p.x(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.y(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.z(), WithinAbs(8, tolerance));
}
