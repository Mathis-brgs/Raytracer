#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_material.hpp"
#include "material/lambert_material.hpp"
#include "render/trace.hpp"
#include "scene/scene.hpp"
#include "test_helpers.hpp"

// A white light behind the eye. The flat material ignores it.
const Light traceLight(Vector(0, 0, -10), Colour(1, 1, 1));
// In every test, the camera ray from the course: from (0, 0, -1) along +z.
const Ray traceRay(Vector(0, 0, -1), Vector(0, 0, 1));

// Orange, not red, so the test proves the colour comes from the sphere's material.
TEST_CASE("a ray that hits the sphere gets its material's colour", "[trace]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    Scene scene(traceLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, orange));

    requireColoursEqual(trace(traceRay, scene), Colour(1, 0.5, 0));
}

// Sphere at (6, 0, 9), radius 5: delta = -44, the ray misses it (see sphere_test.cpp).
TEST_CASE("a ray that misses everything gets black", "[trace]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    Scene scene(traceLight);
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, orange));

    requireColoursEqual(trace(traceRay, scene), Colour(0, 0, 0));
}

// Same sphere: hit at (0, 0, 4), normal (0, 0, -1).
// Light at (3, 0, 0): from the hit, the direction is (3, 0, -4) / 5 = (0.6, 0, -0.8). N . L = 0.8.
// Proves trace gives the material the hit and the scene's light.
TEST_CASE("a ray that hits a lambert sphere gets its colour dimmed by N . L", "[trace]") {
    auto orange = std::make_shared<LambertMaterial>(Colour(1, 0.5, 0));
    Scene scene(Light(Vector(3, 0, 0), Colour(1, 1, 1)));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, orange));

    requireColoursEqual(trace(traceRay, scene), Colour(0.8, 0.4, 0));
}

// The sphere is hit at t = 5, the wall behind it at t = 21 (see scene_test.cpp).
// The wall is added first, so a trace that shades the first shape it finds gets grey.
TEST_CASE("a ray gets the colour of the nearest shape", "[trace]") {
    auto orange = std::make_shared<FlatMaterial>(Colour(1, 0.5, 0));
    auto grey = std::make_shared<FlatMaterial>(Colour(0.8, 0.8, 0.8));
    Scene scene(traceLight);
    scene.add(std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), grey));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, orange));

    requireColoursEqual(trace(traceRay, scene), Colour(1, 0.5, 0));
}
