#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/ray.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

static void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

TEST_CASE("ray.at(t) gives the point O + t * D", "[ray]") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));
    requireVectorsEqual(ray.at(2), Vector(6, 0, 0));
}
