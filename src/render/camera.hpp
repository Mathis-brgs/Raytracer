#pragma once

#include "geometry/ray.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "math/vector.hpp"

// For now, the camera always looks along +z.
class Camera {
private:
    Vector _eye;
    int _width;
    int _height;
    double _distance;

public:
    Camera(const Vector& eye, int width, int height, double distance);

    Vector eye() const;
    int width() const;
    int height() const;
    double distance() const;

    Ray rayThroughCentre() const;
    
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    // Fills every pixel of the image with what its ray sees.
    void render(Image& image, const Sphere& sphere) const;
};
