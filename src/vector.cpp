#include "vector.hpp"

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector::getX() const { return x; }
double Vector::getY() const { return y; }
double Vector::getZ() const { return z; }

Vector Vector::add(const Vector& other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::subtract(const Vector& other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
}
