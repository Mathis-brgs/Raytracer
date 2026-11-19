#include <catch2/catch_test_macros.hpp>

#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "material/flat_material.hpp"
#include "test_helpers.hpp"

// Orange, not red, so the test proves the colour comes from the material.
// The light is below the surface, so a lit material would be black: the flat one ignores it.
TEST_CASE("a flat material shades with its own colour, whatever the light", "[material]") {
    FlatMaterial material(Colour(1, 0.5, 0));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), material};
    Light light(Vector(0, -5, 0), Colour(1, 1, 1));

    requireColoursEqual(material.shade(hit, light), Colour(1, 0.5, 0));
}
