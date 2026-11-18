#include <catch2/catch_test_macros.hpp>

#include "colour/colour.hpp"
#include "test_helpers.hpp"

TEST_CASE("red is 1, 0, 0", "[colour]") {
    requireColourEqual(Colour(1, 0, 0), 1, 0, 0);
}

TEST_CASE("green is 0, 1, 0", "[colour]") {
    requireColourEqual(Colour(0, 1, 0), 0, 1, 0);
}

TEST_CASE("blue is 0, 0, 1", "[colour]") {
    requireColourEqual(Colour(0, 0, 1), 0, 0, 1);
}
