#pragma once

#include <string>

#include "image/image.hpp"

// Writes an image to a file.
// Each output format is its own subclass.
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(Image& image, const std::string& path) = 0;
};
