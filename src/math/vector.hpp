#pragma once

class Vector {
private:
    double _x;
    double _y;
    double _z;

public:
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double t) const;

    // A number, not a Vector: it can't be `*`, which already means scale.
    double dot(const Vector& other) const;
    double length() const;

    // A new Vector of length 1, in the same direction.
    Vector normalised() const;
};

Vector operator*(double t, const Vector& v);
