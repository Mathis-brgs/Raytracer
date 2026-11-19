#pragma once

#include "colour/colour.hpp"

// Declared, not included: hit_info.hpp already includes this file, so including it back would loop.
// A reference parameter only needs the name.
struct HitInfo;
class Light;

class Material {
public:
    virtual ~Material() = default;
    // The colour a ray sees at the hit, lit by the light.
    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
