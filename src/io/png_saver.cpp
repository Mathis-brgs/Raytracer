#include "io/png_saver.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

// A colour channel goes from 0.0 to 1.0. A PNG byte goes from 0 to 255.
// Values outside [0, 1] are clamped first, so 1.2 gives 255 and not a wrapped number.
static unsigned char toByte(double channel) {
    double clamped = std::clamp(channel, 0.0, 1.0);
    return static_cast<unsigned char>(std::round(clamped * 255));
}

void PngSaver::save(Image& image, const std::string& path) {
    // 3 bytes per pixel (red, green, blue), row after row, from the top left.
    std::vector<unsigned char> bytes;
    bytes.reserve(image.width() * image.height() * 3);
    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            Colour colour = image.pixel(x, y);
            bytes.push_back(toByte(colour.r()));
            bytes.push_back(toByte(colour.g()));
            bytes.push_back(toByte(colour.b()));
        }
    }

    // LodePNG compresses the bytes and writes the file. It returns 0 on success.
    unsigned int error = lodepng::encode(path, bytes, image.width(), image.height(), LCT_RGB);
    if (error != 0) {
        throw std::runtime_error("Could not save PNG to " + path + ": " + lodepng_error_text(error));
    }
}
