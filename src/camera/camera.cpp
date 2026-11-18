#include "camera/camera.hpp"

Camera::Camera(const Vector& eye, int width, int height)
    : _eye(eye), _width(width), _height(height) {}

Vector Camera::eye() const { return _eye; }
int Camera::width() const { return _width; }
int Camera::height() const { return _height; }
