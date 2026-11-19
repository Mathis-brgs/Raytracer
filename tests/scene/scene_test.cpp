#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_material.hpp"
#include "scene/scene.hpp"
#include "test_helpers.hpp"

// In every test, the ray goes from (0, 0, -1) along +z.
// Sphere (0, 0, 9), radius 5: hit at t = 5 (point (0, 0, 4)).
// Wall through (0, 0, 20) facing the eye, normal (0, 0, -1): n . D = -1, n . (Q - O) = -21, so t = 21.
// So the sphere is nearer than the wall. Two materials, to tell which shape was hit.
const auto sphereMaterial = std::make_shared<FlatMaterial>(Colour(1, 0, 0));
const auto wallMaterial = std::make_shared<FlatMaterial>(Colour(0.8, 0.8, 0.8));
const Light sceneLight(Vector(0, 0, -10), Colour(1, 1, 1));
const Ray sceneRay(Vector(0, 0, -1), Vector(0, 0, 1));

TEST_CASE("a scene keeps its light", "[scene]") {
    Scene scene(Light(Vector(1, 2, 3), Colour(1, 0.5, 0)));

    requireVectorsEqual(scene.light().position(), Vector(1, 2, 3));
    requireColoursEqual(scene.light().colour(), Colour(1, 0.5, 0));
}

TEST_CASE("an empty scene is never hit", "[scene]") {
    Scene scene(sceneLight);

    REQUIRE_FALSE(scene.nearestHit(sceneRay).has_value());
}

TEST_CASE("a scene with one sphere gives that sphere's hit", "[scene]") {
    Scene scene(sceneLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, sphereMaterial));

    std::optional<HitInfo> hit = scene.nearestHit(sceneRay);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
}

// Both orders, so a scene that keeps the first or the last hit it finds fails one of them.
TEST_CASE("the nearer shape wins when it is added first", "[scene]") {
    Scene scene(sceneLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, sphereMaterial));
    scene.add(std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), wallMaterial));

    std::optional<HitInfo> hit = scene.nearestHit(sceneRay);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    REQUIRE(&hit->material == sphereMaterial.get());
}

TEST_CASE("the nearer shape wins when it is added second", "[scene]") {
    Scene scene(sceneLight);
    scene.add(std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), wallMaterial));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, sphereMaterial));

    std::optional<HitInfo> hit = scene.nearestHit(sceneRay);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    REQUIRE(&hit->material == sphereMaterial.get());
}
