#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "camera/camera.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

TEST_CASE("a camera keeps its eye, its screen size and its screen distance", "[camera]") {
    Camera camera(Vector(1, 2, 3), 640, 480, 1.5);

    REQUIRE_THAT(camera.eye().x(), WithinAbs(1, tolerance));
    REQUIRE_THAT(camera.eye().y(), WithinAbs(2, tolerance));
    REQUIRE_THAT(camera.eye().z(), WithinAbs(3, tolerance));
    REQUIRE(camera.width() == 640);
    REQUIRE(camera.height() == 480);
    REQUIRE_THAT(camera.distance(), WithinAbs(1.5, tolerance));
}
