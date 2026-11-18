#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.hpp"
#include "test_helpers.hpp"

TEST_CASE("ray.at(t) gives the point O + t * D", "[ray]") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));
    requireVectorsEqual(ray.at(2), Vector(6, 0, 0));
}

TEST_CASE("a ray keeps its origin and its direction", "[ray]") {
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));
    requireVectorsEqual(ray.origin(), Vector(1, 2, 3));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}
