#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <string>
#include <vector>

#include "lodepng.h"

#include "io/png_saver.hpp"

static std::string tempPath(const std::string& name) {
    return (std::filesystem::temp_directory_path() / name).string();
}

TEST_CASE("a saved PNG has the size and the pixels of the image", "[png]") {
    std::string path = tempPath("png_saver_size_test.png");
    Image image(3, 2);
    image.setPixel(0, 0, Colour(1, 0, 0));
    image.setPixel(2, 1, Colour(0, 0, 1));

    PngSaver saver;
    saver.save(image, path);

    // Read the file back as RGB: 3 bytes per pixel, row after row.
    std::vector<unsigned char> bytes;
    unsigned int width = 0;
    unsigned int height = 0;
    REQUIRE(lodepng::decode(bytes, width, height, path, LCT_RGB) == 0);

    REQUIRE(width == 3);
    REQUIRE(height == 2);
    // Pixel (0, 0) is the first one: red.
    REQUIRE(bytes[0] == 255);
    REQUIRE(bytes[1] == 0);
    REQUIRE(bytes[2] == 0);
    // Pixel (1, 0) was never set: black.
    REQUIRE(bytes[3] == 0);
    REQUIRE(bytes[4] == 0);
    REQUIRE(bytes[5] == 0);
    // Pixel (2, 1) is the last one: blue.
    REQUIRE(bytes[15] == 0);
    REQUIRE(bytes[16] == 0);
    REQUIRE(bytes[17] == 255);

    std::filesystem::remove(path);
}

// A bright highlight can go above 1. It must become 255, not wrap around.
TEST_CASE("colour values outside [0, 1] are clamped", "[png]") {
    std::string path = tempPath("png_saver_clamp_test.png");
    Image image(1, 1);
    image.setPixel(0, 0, Colour(2, -1, 1));

    PngSaver saver;
    saver.save(image, path);

    std::vector<unsigned char> bytes;
    unsigned int width = 0;
    unsigned int height = 0;
    REQUIRE(lodepng::decode(bytes, width, height, path, LCT_RGB) == 0);

    REQUIRE(bytes[0] == 255);
    REQUIRE(bytes[1] == 0);
    REQUIRE(bytes[2] == 255);

    std::filesystem::remove(path);
}

TEST_CASE("saving to a folder that does not exist throws", "[png]") {
    Image image(1, 1);
    PngSaver saver;

    REQUIRE_THROWS(saver.save(image, "/no/such/folder/out.png"));
}

// 0.5 x 255 = 127.5: we round to the nearest, so 128.
TEST_CASE("a channel at 0.5 is saved as 128", "[png]") {
    std::string path = tempPath("png_saver_round_test.png");
    Image image(1, 1);
    image.setPixel(0, 0, Colour(1, 0.5, 0));

    PngSaver saver;
    saver.save(image, path);

    std::vector<unsigned char> bytes;
    unsigned int width = 0;
    unsigned int height = 0;
    REQUIRE(lodepng::decode(bytes, width, height, path, LCT_RGB) == 0);

    // Compared as ints, so that a failure prints numbers and not characters.
    std::vector<int> actual(bytes.begin(), bytes.end());
    std::vector<int> expected = {255, 128, 0};
    REQUIRE(actual == expected);

    std::filesystem::remove(path);
}
