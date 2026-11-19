#include "render/camera.hpp"

#include "render/trace.hpp"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth) {}

Ray Camera::rayThroughPixel(int column, int row, int width, int height) const {
    double pixelSize = _screenWidth / width;
    // 2.0, not 2: an int divided by an int drops the decimals (5 / 2 is 2).
    // Image rows go down and world y goes up, so y is turned round.
    double x = (column + 0.5 - width / 2.0) * pixelSize;
    double y = (height / 2.0 - row - 0.5) * pixelSize;

    Vector pixel = _screenCentre + Vector(x, y, 0);
    return Ray(_eye, pixel - _eye);
}

// Row by row from the top, left to right: the order the image stores its pixels.
Image Camera::render(const Scene& scene, int width, int height) const {
    Image image(width, height);
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            Ray ray = rayThroughPixel(column, row, width, height);
            image.setPixel(column, row, trace(ray, scene));
        }
    }
    return image;
}
