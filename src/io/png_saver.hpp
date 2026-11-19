#pragma once

#include <string>

#include "io/image_saver.hpp"

// Saves an image to disk as a PNG file, 8 bits per channel, RGB.
class PngSaver : public ImageSaver {
public:
    void save(const Image& image, const std::string& path) const override;
};
