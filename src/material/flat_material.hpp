#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// One colour everywhere. It ignores the hit and the light.
class FlatMaterial : public Material {
private:
    Colour _colour;

public:
    FlatMaterial(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;
};
