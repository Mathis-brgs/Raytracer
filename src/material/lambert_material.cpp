#include "material/lambert_material.hpp"

#include <algorithm>

#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"

LambertMaterial::LambertMaterial(const Colour& colour)
    : _colour(colour) {}

Colour LambertMaterial::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();
    
    double brightness = std::max(0.0, hit.normal.dot(toLight));

    return Colour(_colour.r() * brightness, _colour.g() * brightness, _colour.b() * brightness);
}
