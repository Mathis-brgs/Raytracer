#pragma once

class Vector {
private:
    double x;
    double y;
    double z;

public:
    Vector(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    Vector add(const Vector& other) const;

    // Returns a new Vector: this one minus `other`.
    Vector subtract(const Vector& other) const;
};
