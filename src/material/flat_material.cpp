#include "material/flat_material.hpp"

FlatMaterial::FlatMaterial(const Colour& colour)
    : _colour(colour) {}

// The parameters have no name: they are not used, and the compiler then does not warn about it.
Colour FlatMaterial::shade(const HitInfo&, const Light&) const { return _colour; }
