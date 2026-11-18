#include <catch2/catch_test_macros.hpp>

#include "render/camera.hpp"
#include "test_helpers.hpp"

TEST_CASE("a camera keeps its eye, its screen size and its screen distance", "[camera]") {
    Camera camera(Vector(1, 2, 3), 640, 480, 1.5);

    requireVectorsEqual(camera.eye(), Vector(1, 2, 3));
    REQUIRE(camera.width() == 640);
    REQUIRE(camera.height() == 480);
    REQUIRE_THAT(camera.distance(), WithinAbs(1.5, tolerance));
}

// The camera looks along +z, so the screen centre is the eye plus (0, 0, distance).
// Eye (0, 0, -1), distance 1: screen centre (0, 0, 0), direction (0, 0, 0) - (0, 0, -1) = (0, 0, 1).
TEST_CASE("the ray through the screen centre starts at the eye and goes along +z", "[camera]") {
    Camera camera(Vector(0, 0, -1), 1, 1, 1);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// Eye (1, 2, -1), distance 3: screen centre (1, 2, 2), direction (1, 2, 2) - (1, 2, -1) = (0, 0, 3).
TEST_CASE("the ray through the screen centre follows the eye when it moves", "[camera]") {
    Camera camera(Vector(1, 2, -1), 1, 1, 3);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 3));
}
