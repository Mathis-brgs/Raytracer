#include "render/camera.hpp"

#include "render/trace.hpp"

Camera::Camera(const Vector& eye, double width, double height, double distance)
    : _eye(eye), _width(width), _height(height), _distance(distance) {}

Vector Camera::eye() const { return _eye; }
double Camera::width() const { return _width; }
double Camera::height() const { return _height; }
double Camera::distance() const { return _distance; }

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {
    // _width is a double, so this divides as doubles (an int / int would drop the decimals).
    double pixelSize = _width / imageWidth;

    // Centre of the pixel, measured from the screen centre, in world units.
    // Image rows go down, world y goes up: hence the minus sign on y.
    double x = ((column + 0.5) - imageWidth / 2.) * pixelSize;
    double y = -((row + 0.5) - imageHeight / 2.) * pixelSize;

    // The screen is _distance in front of the eye, along +z.
    Vector pixel = _eye + Vector(x, y, _distance);
    return Ray(_eye, pixel - _eye);
}

// Row by row, top to bottom, left to right: the order the image stores its pixels.
void Camera::render(Image& image, const Sphere& sphere) const {
    for (unsigned int row = 0; row < image.height(); row++) {
        for (unsigned int column = 0; column < image.width(); column++) {
            Ray ray = rayThroughPixel(column, row, image.width(), image.height());
            image.setPixel(column, row, trace(ray, sphere));
        }
    }
}
