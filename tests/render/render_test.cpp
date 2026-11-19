#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <string>
#include <vector>

#include "image/image.hpp"
#include "light/light.hpp"
#include "material/flat_material.hpp"
#include "render/camera.hpp"
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
    Sphere sphere(Vector(0, 0, 9), 1, orangeMaterial);
    Image image = camera.render(sphere, renderLight, 3, 3);

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
    Sphere sphere(Vector(0, 0, 9), 9, orangeMaterial);
    Image image = camera.render(sphere, renderLight, 3, 3);

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
    Sphere sphere(Vector(10, 0, 9), 1, orangeMaterial);
    Image image = camera.render(sphere, renderLight, 3, 1);

    requireColoursEqual(image.pixel(0, 0), black);
    requireColoursEqual(image.pixel(1, 0), black);
    requireColoursEqual(image.pixel(2, 0), orange);
}

// Image 1 x 3. Sphere (0, 10, 9), radius 1: along (0, 10, 10), the same line as (0, 1, 1).
// Image rows go down, so the ray going up is row 0: the top pixel.
TEST_CASE("render: a sphere above colours only the top row", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 1);
    Sphere sphere(Vector(0, 10, 9), 1, orangeMaterial);
    Image image = camera.render(sphere, renderLight, 1, 3);

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
    Sphere sphere(Vector(0, 0, 6), 5, orangeMaterial);
    Image image = camera.render(sphere, renderLight, 5, 3);

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

TEST_CASE("render: the image has the size asked for", "[render]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Sphere sphere(Vector(0, 0, 6), 5, orangeMaterial);

    Image image = camera.render(sphere, renderLight, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}
