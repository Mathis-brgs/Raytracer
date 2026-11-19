#include "render/trace.hpp"

Colour trace(const Ray& ray, const Sphere& sphere) {
    if (sphere.hits(ray)) {
        return sphere.material().shade();
    }
    return Colour(0, 0, 0);
}
