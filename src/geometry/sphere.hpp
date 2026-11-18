#pragma once

#include "math/vector.hpp"
#include "ray/ray.hpp"

class Sphere {
private:
    Vector _centre;
    double _radius;

public:
    Sphere(const Vector& centre, double radius);

    Vector centre() const;
    double radius() const;
    //Est ce que le rayon touche la sphere?
    bool hits(const Ray& ray) const;
    // Si le rayon touche la sphere, retourne le point d'intersection
    Vector hitPoint(const Ray& ray) const;
};
