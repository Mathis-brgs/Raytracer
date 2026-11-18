#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "render/colour_at.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

static void requireColoursEqual(const Colour& actual, const Colour& expected) {
    REQUIRE_THAT(actual.r(), WithinAbs(expected.r(), tolerance));
    REQUIRE_THAT(actual.g(), WithinAbs(expected.g(), tolerance));
    REQUIRE_THAT(actual.b(), WithinAbs(expected.b(), tolerance));
}

// Same sphere as in sphere_test.cpp: it goes from y = 4 (bottom) to y = 14 (top).
const Sphere sphere(Vector(0, 9, 0), 5);

TEST_CASE("a ray hitting the top of the sphere gives red", "[colour_at]") {
    Ray ray(Vector(0, 20, 0), Vector(0, -1, 0)); // going down, hits (0, 14, 0)
    requireColoursEqual(colourAt(sphere, ray), Colour(1, 0, 0));
}

TEST_CASE("a ray hitting the bottom of the sphere gives blue", "[colour_at]") {
    Ray ray(Vector(0, -1, 0), Vector(0, 1, 0)); // going up, hits (0, 4, 0)
    requireColoursEqual(colourAt(sphere, ray), Colour(0, 0, 1));
}

TEST_CASE("a ray hitting the side of the sphere gives green", "[colour_at]") {
    Ray ray(Vector(0, 9, -10), Vector(0, 0, 1)); // at the centre's height, hits (0, 9, -5)
    requireColoursEqual(colourAt(sphere, ray), Colour(0, 1, 0));
}

TEST_CASE("a ray missing the sphere gives black", "[colour_at]") {
    Ray ray(Vector(0, -1, 0), Vector(0, 0, 1)); // 10 below the centre, radius is 5
    requireColoursEqual(colourAt(sphere, ray), Colour(0, 0, 0));
}
