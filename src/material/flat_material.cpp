#include "material/flat_material.hpp"

FlatMaterial::FlatMaterial(const Colour& colour)
    : _colour(colour) {}

Colour FlatMaterial::shade() const { return _colour; }
