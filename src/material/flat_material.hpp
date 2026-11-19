#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

class FlatMaterial : public Material {
private:
    Colour _colour;

public:
    FlatMaterial(const Colour& colour);

    Colour shade() const override;
};
