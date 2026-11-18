#include "render/colour_at.hpp"

Colour colourAt(const Sphere& sphere, const Ray& ray) {
    if (!sphere.hits(ray)) {
        return Colour(0, 0, 0);
    }

    Vector P = sphere.hitPoint(ray);
    Vector C = sphere.centre();

    if (P.y() > C.y()) {
        return Colour(1, 0, 0);
    }
    if (P.y() < C.y()) {
        return Colour(0, 0, 1);
    }
    return Colour(0, 1, 0);
}
