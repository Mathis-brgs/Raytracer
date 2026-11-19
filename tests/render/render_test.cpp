#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <string>
#include <vector>

#include "image/image.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_material.hpp"
#include "material/lambert_material.hpp"
#include "render/camera.hpp"
#include "scene/scene.hpp"
#include "test_helpers.hpp"

// In every test, the eye is (0, 0, -1), the screen centre (0, 0, 0), and a pixel is 1 x 1.
// So the ray through a pixel goes from the eye along (x, y, 1), with x and y in {-1, 0, 1}.
// Orange, not red, so the tests prove the colour comes from the sphere's material.
const Colour orange(1, 0.5, 0);
const Colour black(0, 0, 0);
const auto orangeMaterial = std::make_shared<FlatMaterial>(orange);
// The flat material ignores the light, so any light will do.
const Light renderLight(Vector(0, 0, -10), Colour(1, 1, 1));

// Sphere (0, 0, 9), radius 1, 10 in front of the eye.
// Centre ray (0, 0, 1): goes through the sphere centre, hits.
// Side ray (0, 1, 1): passes sqrt(50) ~ 7.1 from the centre, misses. Corner (1, 1, 1): sqrt(200/3) ~ 8.2, misses.
TEST_CASE("render: a small sphere ahead colours only the centre pixel", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 3);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 1, orangeMaterial));
    Image image = camera.render(scene, 3, 3);

    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            if (x == 1 && y == 1) {
                requireColoursEqual(image.pixel(x, y), orange);
            } else {
                requireColoursEqual(image.pixel(x, y), black);
            }
        }
    }
}

// Same sphere with radius 9: every ray passes at most ~8.2 from the centre, so every ray hits.
TEST_CASE("render: a big sphere ahead colours every pixel", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 3);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 9, orangeMaterial));
    Image image = camera.render(scene, 3, 3);

    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            requireColoursEqual(image.pixel(x, y), orange);
        }
    }
}

// Image 3 x 1. Sphere (10, 0, 9), radius 1: from the eye it is along (10, 0, 10), the same line as (1, 0, 1).
// Only the right pixel (column 2) looks that way. Centre ray (0, 0, 1) passes 10 from the centre, misses.
TEST_CASE("render: a sphere on the right colours only the right column", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 3);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(10, 0, 9), 1, orangeMaterial));
    Image image = camera.render(scene, 3, 1);

    requireColoursEqual(image.pixel(0, 0), black);
    requireColoursEqual(image.pixel(1, 0), black);
    requireColoursEqual(image.pixel(2, 0), orange);
}

// Image 1 x 3. Sphere (0, 10, 9), radius 1: along (0, 10, 10), the same line as (0, 1, 1).
// Image rows go down, so the ray going up is row 0: the top pixel.
TEST_CASE("render: a sphere above colours only the top row", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 1);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 10, 9), 1, orangeMaterial));
    Image image = camera.render(scene, 1, 3);

    requireColoursEqual(image.pixel(0, 0), orange);
    requireColoursEqual(image.pixel(0, 1), black);
    requireColoursEqual(image.pixel(0, 2), black);
}

// The course's grid: screen 5 x 3, image 5 x 3, sphere (0, 0, 6), radius 5.
// L = O - C = (0, 0, -7), so b = -14 and c = 24 for every pixel, and delta = 196 - 96a with a = D.D.
// A ray hits when a = x^2 + y^2 + 1 <= 2: the centre and its four neighbours, a plus.
// Diagonals have a = 3 (delta = -92), so they miss.
TEST_CASE("render: the course's sphere at (0, 0, 6) draws a plus", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, orangeMaterial));
    Image image = camera.render(scene, 5, 3);

    std::vector<std::string> expected = {
        "..#..",
        ".###.",
        "..#..",
    };
    for (unsigned int row = 0; row < 3; row++) {
        for (unsigned int column = 0; column < 5; column++) {
            if (expected[row][column] == '#') {
                requireColoursEqual(image.pixel(column, row), orange);
            } else {
                requireColoursEqual(image.pixel(column, row), black);
            }
        }
    }
}

// Same grid and sphere, now Lambert, with a white light at (0, 0, -2).
// Centre ray, D = (0, 0, 1): a = 1, delta = 100, t = 2, P = (0, 0, 1), N = (0, 0, -1).
//   P to light: (0, 0, -3), so L = (0, 0, -1). N . L = 1: full orange.
// Right ray, D = (1, 0, 1): a = 2, delta = 4, t = 3, P = (3, 0, 2), N = (3, 0, -4) / 5 = (0.6, 0, -0.8).
//   P to light: (-3, 0, -4), length 5, so L = (-0.6, 0, -0.8). N . L = -0.36 + 0.64 = 0.28.
// The other three neighbours are the same by symmetry: 0.28 x orange = (0.28, 0.14, 0).
TEST_CASE("render: the lit plus is brightest in the middle", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    auto lambertOrange = std::make_shared<LambertMaterial>(orange);
    Scene scene(Light(Vector(0, 0, -2), Colour(1, 1, 1)));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, lambertOrange));
    Image image = camera.render(scene, 5, 3);

    const Colour dimOrange(0.28, 0.14, 0);
    std::vector<std::string> expected = {
        "..#..",
        ".#O#.",
        "..#..",
    };
    for (unsigned int row = 0; row < 3; row++) {
        for (unsigned int column = 0; column < 5; column++) {
            if (expected[row][column] == 'O') {
                requireColoursEqual(image.pixel(column, row), orange);
            } else if (expected[row][column] == '#') {
                requireColoursEqual(image.pixel(column, row), dimOrange);
            } else {
                requireColoursEqual(image.pixel(column, row), black);
            }
        }
    }
}

TEST_CASE("render: the image has the size asked for", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Scene scene(renderLight);
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, orangeMaterial));

    Image image = camera.render(scene, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}
