#pragma once

#include "material/material.hpp"
#include "math/vector.hpp"


struct HitInfo {
    double t;       
    Vector point;
    Vector normal; 
    const Material& material;
};
