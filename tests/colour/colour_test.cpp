#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "colour/colour.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

TEST_CASE("red is 1, 0, 0", "[colour]") {
    Colour red(1, 0, 0);

    REQUIRE_THAT(red.r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(red.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(red.b(), WithinAbs(0, tolerance));
}

TEST_CASE("green is 0, 1, 0", "[colour]") {
    Colour green(0, 1, 0);

    REQUIRE_THAT(green.r(), WithinAbs(0, tolerance));
    REQUIRE_THAT(green.g(), WithinAbs(1, tolerance));
    REQUIRE_THAT(green.b(), WithinAbs(0, tolerance));
}

TEST_CASE("blue is 0, 0, 1", "[colour]") {
    Colour blue(0, 0, 1);

    REQUIRE_THAT(blue.r(), WithinAbs(0, tolerance));
    REQUIRE_THAT(blue.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(blue.b(), WithinAbs(1, tolerance));
}
