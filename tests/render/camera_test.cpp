#include <catch2/catch_test_macros.hpp>

#include "render/camera.hpp"
#include "test_helpers.hpp"

// The spike's single pixel is the one pixel of a 1 x 1 image: its centre is the screen centre.
// Eye (0, 0, -1), screen centre (0, 0, 0): direction (0, 0, 0) - (0, 0, -1) = (0, 0, 1).
TEST_CASE("in a 1 x 1 image, the ray goes from the eye to the screen centre", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 1);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// Eye (1, 2, -1), screen centre (1, 2, 2): direction (1, 2, 2) - (1, 2, -1) = (0, 0, 3).
TEST_CASE("in a 1 x 1 image, the ray follows the eye when it moves", "[camera]") {
    Camera camera(Vector(1, 2, -1), Vector(1, 2, 2), 1);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 3));
}

// Eye (0, 0, -1), screen centre (0, 0, 0), screen 5 wide. Image 5 x 3: a pixel is 1 across.
// A pixel centre is at x = (column + 0.5 - 5/2), y = (3/2 - row - 0.5), z = 0.
TEST_CASE("rayThroughPixel: the centre pixel (2, 1) goes straight along +z", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// x = 4.5 - 2.5 = 2, y = 1.5 - 0 - 0.5 = 1.
TEST_CASE("rayThroughPixel: the top right pixel (4, 0) goes right and up", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

// x = 0.5 - 2.5 = -2, y = 1.5 - 2 - 0.5 = -1.
TEST_CASE("rayThroughPixel: the bottom left pixel (0, 2) goes left and down", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}

// Screen 2 wide, image 512 x 256: a pixel is 2 / 512 = 1/256 wide, not 1.
// Width and height differ on purpose: swapping x and y would give other values.
// Top left (0, 0):         x = (0.5 - 256) / 256 = -0.998046875, y = (128 - 0.5) / 256 = 0.498046875.
// Bottom right (511, 255): x = (511.5 - 256) / 256 = 0.998046875, y = (128 - 255.5) / 256 = -0.498046875.
TEST_CASE("rayThroughPixel scales by the pixel size when a pixel is not 1 wide", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    Ray topLeft = camera.rayThroughPixel(0, 0, 512, 256);
    requireVectorsEqual(topLeft.origin(), Vector(0, 0, -1));
    requireVectorsEqual(topLeft.direction(), Vector(-0.998046875, 0.498046875, 1));

    Ray bottomRight = camera.rayThroughPixel(511, 255, 512, 256);
    requireVectorsEqual(bottomRight.direction(), Vector(0.998046875, -0.498046875, 1));
}
