#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// A matte surface (Lambert's law): the more it faces the light, the brighter it is.
class LambertMaterial : public Material {
private:
    Colour _colour;

public:
    LambertMaterial(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;
};
