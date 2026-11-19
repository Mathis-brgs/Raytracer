#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/plane.hpp"
#include "material/flat_material.hpp"
#include "test_helpers.hpp"

// A plane is hit at t = n . (Q - O) / (n . D): Q a point on it, n its normal, O and D the ray's.
// In most tests the plane is a floor: through Q = (0, -5, 0), facing up, n = (0, 1, 0).
const auto grey = std::make_shared<FlatMaterial>(Colour(0.8, 0.8, 0.8));

// Ray from (0, 0, -1) along (0, -1, 1): down and forward.
// n . D = -1, n . (Q - O) = n . (0, -5, 1) = -5, so t = 5. Point: (0, 0, -1) + 5 (0, -1, 1) = (0, -5, 4).
TEST_CASE("a ray going down hits the floor", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey);
    Ray ray(Vector(0, 0, -1), Vector(0, -1, 1));

    std::optional<HitInfo> hit = floor.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, -5, 4));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
}

// Ray along (0, 0, 1): n . D = 0. The ray runs alongside the floor and never meets it.
TEST_CASE("a ray parallel to the floor misses it", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    REQUIRE_FALSE(floor.intersect(ray).has_value());
}

// Ray going up, along (0, 1, 0): n . D = 1, n . (Q - O) = -5, so t = -5: the floor is behind.
TEST_CASE("a ray going up does not hit the floor behind it", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey);
    Ray ray(Vector(0, 0, 0), Vector(0, 1, 0));

    REQUIRE_FALSE(floor.intersect(ray).has_value());
}

// A wall leaning back, through (0, 0, 10), normal given as (0, 1, -1): length sqrt(2), not 1.
// The plane must normalise it: n = (0, sqrt(0.5), -sqrt(0.5)).
// Ray from the origin along (0, 0, 1): n . D = -sqrt(0.5), n . (Q - O) = -10 sqrt(0.5), so t = 10.
TEST_CASE("a tilted plane gives a normal of length 1", "[plane]") {
    Plane wall(Vector(0, 0, 10), Vector(0, 1, -1), grey);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    std::optional<HitInfo> hit = wall.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(10, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 10));
    requireVectorsEqual(hit->normal, Vector(0, std::sqrt(0.5), -std::sqrt(0.5)));
}

// Through a Shape reference, and the hit carries this plane's material (same object).
TEST_CASE("a plane is a shape and its hit carries its material", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey);
    const Shape& shape = floor;
    Ray ray(Vector(0, 0, -1), Vector(0, -1, 1));

    std::optional<HitInfo> hit = shape.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE(&hit->material == grey.get());
}
