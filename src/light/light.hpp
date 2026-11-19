#pragma once

#include "colour/colour.hpp"
#include "math/vector.hpp"

class Light {
private:
    Vector _position;
    Colour _colour;

public:
    Light(const Vector& position, const Colour& colour);

    Vector position() const;
    Colour colour() const;
};
