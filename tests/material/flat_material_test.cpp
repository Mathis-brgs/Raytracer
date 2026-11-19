#include <catch2/catch_test_macros.hpp>

#include "material/flat_material.hpp"
#include "test_helpers.hpp"

// Orange, not red, so the test proves the colour comes from the material.
TEST_CASE("a flat material shades with its own colour", "[material]") {
    FlatMaterial material(Colour(1, 0.5, 0));

    requireColoursEqual(material.shade(), Colour(1, 0.5, 0));
}
