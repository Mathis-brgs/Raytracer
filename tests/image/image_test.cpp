#include <catch2/catch_test_macros.hpp>

#include "image/image.hpp"
#include "test_helpers.hpp"

TEST_CASE("an image keeps its width and its height", "[image]") {
    Image image(6, 5);

    REQUIRE(image.width() == 6);
    REQUIRE(image.height() == 5);
}

TEST_CASE("every pixel of a new image is black", "[image]") {
    Image image(6, 5);

    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            requireColoursEqual(image.pixel(x, y), Colour(0, 0, 0));
        }
    }
}

// Width 6 and height 5 are different on purpose: swapping x and y would hit another pixel.
TEST_CASE("setPixel(3, 2) colours column 3, row 2, and nothing else", "[image]") {
    Image image(6, 5);

    image.setPixel(3, 2, Colour(1, 0, 0));

    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            if (x == 3 && y == 2) {
                requireColoursEqual(image.pixel(x, y), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(x, y), Colour(0, 0, 0));
            }
        }
    }
}
