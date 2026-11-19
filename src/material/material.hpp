#pragma once

#include "colour/colour.hpp"

class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade() const = 0;
};
