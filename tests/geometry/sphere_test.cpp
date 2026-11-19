#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "geometry/sphere.hpp"
#include "material/flat_material.hpp"
#include "test_helpers.hpp"

// All the spheres here use this material.
const auto red = std::make_shared<FlatMaterial>(Colour(1, 0, 0));

TEST_CASE("a ray aimed at the centre hits the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1, red);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));
    REQUIRE(sphere.intersect(ray).has_value());
}

TEST_CASE("a ray passing above the sphere misses it", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1, red);
    Ray ray(Vector(0, 2, -5), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

// t = 5 (point (0, 4, 0)) or t = 15 (point (0, 14, 0)). The nearest is (0, 4, 0).
// The normal goes from the centre (0, 9, 0) to that point: straight down.
TEST_CASE("a ray going up the y axis hits the bottom of the sphere", "[sphere]") {
    Sphere sphere(Vector(0, 9, 0), 5, red);
    Ray ray(Vector(0, -1, 0), Vector(0, 1, 0));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 4, 0));
    requireVectorsEqual(hit->normal, Vector(0, -1, 0));
}

TEST_CASE("a sphere behind the eye is not hit", "[sphere]") {
    Sphere sphere(Vector(0, 0, -10), 1, red);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

// t = -2 (behind) or t = 2. Only t = 2 is in front: point (0, 0, 2), normal along +z.
TEST_CASE("a ray starting inside the sphere hits it in front, not behind", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 2, red);
    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 2));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}

// Ray from (0, 0, -1) along +z. Sphere at (3, 0, 9), radius 5:
// L = (-3, 0, -10), b = -20, c = 109 - 25 = 84, delta = 400 - 336 = 64, so t = 6 or 14.
// Nearest point: (0, 0, 5). Point - centre = (-3, 0, -4), length 5, so the normal is (-0.6, 0, -0.8).
TEST_CASE("a ray hits a sphere that is off-centre but close enough", "[sphere]") {
    Sphere sphere(Vector(3, 0, 9), 5, red);
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

// Sphere at (6, 0, 9), radius 5: c = 136 - 25 = 111, delta = 400 - 444 = -44, so no hit.
TEST_CASE("a ray misses a sphere that is too far to the side", "[sphere]") {
    Sphere sphere(Vector(6, 0, 9), 5, red);
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

// The same object, not just an equal one: the addresses match.
TEST_CASE("a hit carries the sphere's material", "[sphere]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    Sphere sphere(Vector(0, 0, 0), 1, orange);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));

    std::optional<HitInfo> hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());
    REQUIRE(&hit->material == orange.get());
}

TEST_CASE("a sphere keeps its centre, its radius and its material", "[sphere]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    Sphere sphere(Vector(1, 2, 3), 5, orange);

    requireVectorsEqual(sphere.centre(), Vector(1, 2, 3));
    REQUIRE_THAT(sphere.radius(), WithinAbs(5, tolerance));
    REQUIRE(&sphere.material() == orange.get());
}

// Through a Shape reference, the call goes to Sphere::intersect (a virtual function).
// Same ray and sphere as the first test: it hits.
TEST_CASE("a sphere can be used as a shape", "[sphere]") {
    Sphere sphere(Vector(0, 0, 0), 1, red);
    const Shape& shape = sphere;
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));

    REQUIRE(shape.intersect(ray).has_value());
}
