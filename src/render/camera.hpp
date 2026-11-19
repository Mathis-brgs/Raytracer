#pragma once

#include "geometry/ray.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "math/vector.hpp"

// An eye and a screen in front of it. For now, the screen faces along +z.
class Camera {
private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;

public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    // The ray from the eye through the centre of pixel (column, row),
    // in an image width x height pixels that covers the whole screen.
    Ray rayThroughPixel(int column, int row, int width, int height) const;

    // An image of width x height pixels, each with the colour its ray sees.
    Image render(const Sphere& sphere, int width, int height) const;
};
