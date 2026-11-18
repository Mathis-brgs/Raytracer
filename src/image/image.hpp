#pragma once

#include <vector>

#include "colour/colour.hpp"

// A grid of pixels. (0, 0) is the top left pixel: x goes right, y goes down.
// Every pixel starts black.
class Image {
private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;

public:
    Image(unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;

    void setPixel(unsigned int x, unsigned int y, const Colour& colour);
    Colour pixel(unsigned int x, unsigned int y) const;
};
