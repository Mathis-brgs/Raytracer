#pragma once

#include <string>

#include "image/image.hpp"

// Writes an image to a file.
// Each output format is its own subclass.
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    // Every saver writes the whole image to path, or throws a std::runtime_error.
    virtual void save(const Image& image, const std::string& path) const = 0;
};
