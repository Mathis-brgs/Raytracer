#include "material/lambert_material.hpp"

#include <algorithm>

#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"

LambertMaterial::LambertMaterial(const Colour& colour)
    : _colour(colour) {}

Colour LambertMaterial::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();

    // Both vectors have length 1, so the dot product is the cosine of the angle between them:
    // 1 when the light is straight above, 0 when it grazes the surface, negative when it is behind.
    // Behind gets no light, not a negative amount, hence the max with 0.
    double brightness = std::max(0.0, hit.normal.dot(toLight));

    return Colour(_colour.r() * brightness, _colour.g() * brightness, _colour.b() * brightness);
}
