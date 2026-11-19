#include <catch2/catch_test_macros.hpp>

#include "render/camera.hpp"
#include "test_helpers.hpp"

TEST_CASE("a camera keeps its eye, its screen size and its screen distance", "[camera]") {
    Camera camera(Vector(1, 2, 3), 640, 480, 1.5);

    requireVectorsEqual(camera.eye(), Vector(1, 2, 3));
    REQUIRE_THAT(camera.width(), WithinAbs(640, tolerance));
    REQUIRE_THAT(camera.height(), WithinAbs(480, tolerance));
    REQUIRE_THAT(camera.distance(), WithinAbs(1.5, tolerance));
}

// The spike's single pixel is the one pixel of a 1 x 1 image: its centre is the screen centre.
// The camera looks along +z, so the screen centre is the eye plus (0, 0, distance).
// Eye (0, 0, -1), distance 1: screen centre (0, 0, 0), direction (0, 0, 0) - (0, 0, -1) = (0, 0, 1).
TEST_CASE("in a 1 x 1 image, the ray goes from the eye along +z", "[camera]") {
    Camera camera(Vector(0, 0, -1), 1, 1, 1);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// Eye (1, 2, -1), distance 3: screen centre (1, 2, 2), direction (1, 2, 2) - (1, 2, -1) = (0, 0, 3).
TEST_CASE("in a 1 x 1 image, the ray follows the eye when it moves", "[camera]") {
    Camera camera(Vector(1, 2, -1), 1, 1, 3);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 3));
}

// Screen 5 wide and 3 high, 1 in front of the eye. Image 5 columns, 3 rows: a pixel is 1 x 1.
// A pixel centre is at x = (column + 0.5 - 5/2), y = -(row + 0.5 - 3/2), z = 1 from the eye.
TEST_CASE("rayThroughPixel: the centre pixel (2, 1) goes straight along +z", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5, 3, 1);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// x = 4.5 - 2.5 = 2, y = -(0.5 - 1.5) = 1.
TEST_CASE("rayThroughPixel: the top right pixel (4, 0) goes right and up", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5, 3, 1);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

// x = 0.5 - 2.5 = -2, y = -(2.5 - 1.5) = -1. z stays 1: the screen is in front of the eye.
TEST_CASE("rayThroughPixel: the bottom left pixel (0, 2) goes left and down", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5, 3, 1);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}

// Screen 2 wide and 1 high, image 512 x 256: a pixel is 2 / 512 = 1/256 wide, not 1.
// Width and height differ on purpose: swapping x and y would give other values.
// Top left (0, 0):       x = (0.5 - 256) / 256 = -0.998046875, y = -(0.5 - 128) / 256 = 0.498046875.
// Bottom right (511, 255): x = (511.5 - 256) / 256 = 0.998046875, y = -(255.5 - 128) / 256 = -0.498046875.
TEST_CASE("rayThroughPixel scales by the pixel size when a pixel is not 1 wide", "[camera]") {
    Camera camera(Vector(0, 0, -1), 2, 1, 1);

    Ray topLeft = camera.rayThroughPixel(0, 0, 512, 256);
    requireVectorsEqual(topLeft.origin(), Vector(0, 0, -1));
    requireVectorsEqual(topLeft.direction(), Vector(-0.998046875, 0.498046875, 1));

    Ray bottomRight = camera.rayThroughPixel(511, 255, 512, 256);
    requireVectorsEqual(bottomRight.direction(), Vector(0.998046875, -0.498046875, 1));
}
