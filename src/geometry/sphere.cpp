#include "geometry/sphere.hpp"

#include <algorithm>
#include <cmath>

Sphere::Sphere(const Vector& centre, double radius, std::shared_ptr<const Material> material)
    : _centre(centre), _radius(radius), _material(material) {}

Vector Sphere::centre() const { return _centre; }
double Sphere::radius() const { return _radius; }
const Material& Sphere::material() const { return *_material; }

std::optional<HitInfo> Sphere::intersect(const Ray& ray) const {
    Vector O = ray.origin();
    Vector D = ray.direction();
    Vector C = _centre;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0) {
        return std::nullopt;
    }

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    // A negative t is behind the ray's origin: ignore it. Of two positive t, keep the nearest.
    double t;
    if (t1 > 0 && t2 > 0) {
        t = std::min(t1, t2);
    } else if (t1 > 0) {
        t = t1;
    } else if (t2 > 0) {
        t = t2;
    } else {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _centre).normalised();
    return HitInfo{point, normal, *_material};
}
