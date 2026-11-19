#pragma once

#include <memory>

#include "material/material.hpp"
#include "math/vector.hpp"


struct HitInfo {
    Vector point;
    Vector normal;
    const Material& material;
};
