#include "render/trace.hpp"

Colour trace(const Ray& ray, const Sphere& sphere) {
    if (sphere.hits(ray)) {
        return sphere.colour();
    }
    return Colour(0, 0, 0);
}
