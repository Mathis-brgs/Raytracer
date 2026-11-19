#include <catch2/catch_test_macros.hpp>

#include "light/light.hpp"
#include "test_helpers.hpp"

TEST_CASE("a light keeps its position and its colour", "[light]") {
    Light light(Vector(1, 2, 3), Colour(1, 0.5, 0));

    requireVectorsEqual(light.position(), Vector(1, 2, 3));
    requireColoursEqual(light.colour(), Colour(1, 0.5, 0));
}
