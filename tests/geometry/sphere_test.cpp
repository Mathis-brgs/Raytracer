#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/sphere.hpp"
#include "material/flat_material.hpp"
#include "test_helpers.hpp"

// The geometry tests do not look at the material, so they all share this one.
const auto red = std::make_shared<FlatMaterial>(Colour(1, 0, 0));

TEST_CASE("a ray aimed at the centre hits the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1, red);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));
    REQUIRE(sphere.hits(ray));
}

TEST_CASE("a ray passing above the sphere misses it", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1, red);
    Ray ray(Vector(0, 2, -5), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.hits(ray));
}

TEST_CASE("a ray going up the y axis hits the bottom of the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 9, 0), 5, red);
    Ray ray(Vector(0, -1, 0), Vector(0, 1, 0));

    Vector p = sphere.hitPoint(ray);

    REQUIRE_THAT(p.x(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.y(), WithinAbs(4, tolerance));
    REQUIRE_THAT(p.z(), WithinAbs(0, tolerance));
}


TEST_CASE("a sphere behind the eye is not hit", "[sphere]") {
    Sphere sphere(Vector(0, 0, -10), 1, red);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.hits(ray));
}

TEST_CASE("a ray starting inside the sphere hits it in front, not behind", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 2, red);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    Vector p = sphere.hitPoint(ray);

    REQUIRE_THAT(p.x(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.y(), WithinAbs(0, tolerance));
    REQUIRE_THAT(p.z(), WithinAbs(2, tolerance));
}

// Ray from (0, 0, -1) along +z. Sphere at (3, 0, 9), radius 5:
// L = (-3, 0, -10), b = -20, c = 109 - 25 = 84, delta = 400 - 336 = 64, so t = 6 or 14.
TEST_CASE("a ray hits a sphere that is off-centre but close enough", "[sphere]") {
    Sphere sphere(Vector(3, 0, 9), 5, red);
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    REQUIRE(sphere.hits(ray));
}

// Sphere at (6, 0, 9), radius 5: c = 136 - 25 = 111, delta = 400 - 444 = -44, so no hit.
TEST_CASE("a ray misses a sphere that is too far to the side", "[sphere]") {
    Sphere sphere(Vector(6, 0, 9), 5, red);
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.hits(ray));
}

TEST_CASE("a sphere keeps its centre, its radius and its material", "[sphere]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    Sphere sphere(Vector(1, 2, 3), 5, orange);

    requireVectorsEqual(sphere.centre(), Vector(1, 2, 3));
    REQUIRE_THAT(sphere.radius(), WithinAbs(5, tolerance));
    requireColoursEqual(sphere.material().shade(), Colour(1, 0.5, 0));
}
