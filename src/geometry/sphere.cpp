#include "geometry/sphere.hpp"

#include <cmath>

Sphere::Sphere(const Vector& centre, double radius, const Colour& colour)
    : _centre(centre), _radius(radius), _colour(colour) {}

Vector Sphere::centre() const { return _centre; }
double Sphere::radius() const { return _radius; }
Colour Sphere::colour() const { return _colour; }

bool Sphere::hits(const Ray& ray) const {
    Vector O = ray.origin();
    Vector D = ray.direction();
    Vector C = _centre;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0) {
        return false;
    }

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    return t1 > 0 || t2 > 0;
}

// Call only when hits(ray) is true.
Vector Sphere::hitPoint(const Ray& ray) const {
    Vector O = ray.origin();
    Vector D = ray.direction();
    Vector C = _centre;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4 * a * c;

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    // t2 is the nearer point. If it is behind the eye, the ray started inside the sphere.
    if (t2 > 0) {
        return ray.at(t2);
    }
    return ray.at(t1);
}
