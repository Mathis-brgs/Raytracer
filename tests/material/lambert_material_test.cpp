#include <catch2/catch_test_macros.hpp>

#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "material/lambert_material.hpp"
#include "test_helpers.hpp"

// In every test, the surface is hit at the origin and faces up: normal (0, 1, 0).
// Orange, so the tests show each channel is scaled by the same amount.
const Colour lambertOrange(1, 0.5, 0);
const Colour white(1, 1, 1);

// Direction to the light: (0, 5, 0) normalised is (0, 1, 0). N . L = 1: full colour.
TEST_CASE("lambert: a light straight above gives the full colour", "[material]") {
    LambertMaterial material(lambertOrange);
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), material};
    Light light(Vector(0, 5, 0), white);

    requireColoursEqual(material.shade(hit, light), Colour(1, 0.5, 0));
}

// Direction to the light: (4, 3, 0) has length 5, so it is (0.8, 0.6, 0). N . L = 0.6.
TEST_CASE("lambert: a light at a slant dims the colour by N . L", "[material]") {
    LambertMaterial material(lambertOrange);
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), material};
    Light light(Vector(4, 3, 0), white);

    requireColoursEqual(material.shade(hit, light), Colour(0.6, 0.3, 0));
}

// Direction to the light: (1, 0, 0). N . L = 0: the light grazes the surface.
TEST_CASE("lambert: a light level with the surface gives black", "[material]") {
    LambertMaterial material(lambertOrange);
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), material};
    Light light(Vector(7, 0, 0), white);

    requireColoursEqual(material.shade(hit, light), Colour(0, 0, 0));
}

// Direction to the light: (0, -1, 0). N . L = -1. A negative amount of light makes no sense: black.
TEST_CASE("lambert: a light behind the surface gives black, not a negative colour", "[material]") {
    LambertMaterial material(lambertOrange);
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), material};
    Light light(Vector(0, -5, 0), white);

    requireColoursEqual(material.shade(hit, light), Colour(0, 0, 0));
}
