#include <iostream>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "render/camera.hpp"
#include "render/trace.hpp"

// The colour of one pixel: the ray from the eye through the centre of the screen.
int main() {
    Camera camera(Vector(0, 0, -1), 1, 1, 1);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Ray ray = camera.rayThroughCentre();
    Colour pixel = trace(ray, sphere);

    std::cout << "(" << pixel.r() << ", " << pixel.g() << ", " << pixel.b() << ")\n";
    return 0;
}
