#include "render/camera.hpp"

Camera::Camera(const Vector& eye, int width, int height, double distance)
    : _eye(eye), _width(width), _height(height), _distance(distance) {}

Vector Camera::eye() const { return _eye; }
int Camera::width() const { return _width; }
int Camera::height() const { return _height; }
double Camera::distance() const { return _distance; }

Ray Camera::rayThroughCentre() const {
    Vector screenCentre = _eye + Vector(0, 0, _distance);
    return Ray(_eye, screenCentre - _eye);
}
