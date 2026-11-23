#include "geometry/plane.hpp"

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(material) {}

// A point P is on the plane when n . (P - Q) = 0. Put P = O + t D in it and solve for t:
// t = n . (Q - O) / (n . D).
std::optional<HitInfo> Plane::intersect(const Ray& ray) const {
    double nDotD = _normal.dot(ray.direction());
    if (nDotD == 0.0) {
        return std::nullopt; // the ray runs alongside the plane
    }

    double t = _normal.dot(_point - ray.origin()) / nDotD;
    if (t <= 0.0) {
        return std::nullopt; // the plane is behind the ray's origin
    }

    return HitInfo{t, ray.at(t), _normal, *_material};
}
