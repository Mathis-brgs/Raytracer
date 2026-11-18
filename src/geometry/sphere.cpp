#include "geometry/sphere.hpp"

#include <cmath>

Sphere::Sphere(const Vector& centre, double radius)
    : _centre(centre), _radius(radius) {}

Vector Sphere::centre() const { return _centre; }
double Sphere::radius() const { return _radius; }

bool Sphere::hits(const Ray& ray) const {
    Vector oc = ray.origin() - _centre;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * oc.dot(ray.direction());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}

Vector Sphere::hitPoint(const Ray& ray) const {
    Vector oc = ray.origin() - _centre;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * oc.dot(ray.direction());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;
    double t = (-b - std::sqrt(discriminant)) / (2 * a);
    return ray.at(t);
}
