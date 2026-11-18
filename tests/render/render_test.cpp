#include <catch2/catch_test_macros.hpp>

#include "image/image.hpp"
#include "render/camera.hpp"
#include "test_helpers.hpp"

// In every test, a pixel is 1 x 1 and the screen is 1 in front of the eye (0, 0, -1).
// So the ray through a pixel goes from the eye along (x, y, 1), with x and y in {-1, 0, 1}.
// Orange, not red, so the tests prove the colour comes from the sphere.
const Colour orange(1, 0.5, 0);
const Colour black(0, 0, 0);

// Sphere (0, 0, 9), radius 1, 10 in front of the eye.
// Centre ray (0, 0, 1): goes through the sphere centre, hits.
// Side ray (0, 1, 1): passes sqrt(50) ~ 7.1 from the centre, misses. Corner (1, 1, 1): sqrt(200/3) ~ 8.2, misses.
TEST_CASE("render: a small sphere ahead colours only the centre pixel", "[render]") {
    Camera camera(Vector(0, 0, -1), 3, 3, 1);
    Sphere sphere(Vector(0, 0, 9), 1, orange);
    Image image(3, 3);

    camera.render(image, sphere);

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
    Camera camera(Vector(0, 0, -1), 3, 3, 1);
    Sphere sphere(Vector(0, 0, 9), 9, orange);
    Image image(3, 3);

    camera.render(image, sphere);

    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            requireColoursEqual(image.pixel(x, y), orange);
        }
    }
}

// Image 3 x 1. Sphere (10, 0, 9), radius 1: from the eye it is along (10, 0, 10), the same line as (1, 0, 1).
// Only the right pixel (column 2) looks that way. Centre ray (0, 0, 1) passes 10 from the centre, misses.
TEST_CASE("render: a sphere on the right colours only the right column", "[render]") {
    Camera camera(Vector(0, 0, -1), 3, 1, 1);
    Sphere sphere(Vector(10, 0, 9), 1, orange);
    Image image(3, 1);

    camera.render(image, sphere);

    requireColoursEqual(image.pixel(0, 0), black);
    requireColoursEqual(image.pixel(1, 0), black);
    requireColoursEqual(image.pixel(2, 0), orange);
}

// Image 1 x 3. Sphere (0, 10, 9), radius 1: along (0, 10, 10), the same line as (0, 1, 1).
// Image rows go down, so the ray going up is row 0: the top pixel.
TEST_CASE("render: a sphere above colours only the top row", "[render]") {
    Camera camera(Vector(0, 0, -1), 1, 3, 1);
    Sphere sphere(Vector(0, 10, 9), 1, orange);
    Image image(1, 3);

    camera.render(image, sphere);

    requireColoursEqual(image.pixel(0, 0), orange);
    requireColoursEqual(image.pixel(0, 1), black);
    requireColoursEqual(image.pixel(0, 2), black);
}
