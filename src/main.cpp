#include <iostream>
#include <string>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "math/vector.hpp"
#include "render/camera.hpp"

// Renders one red sphere and saves it as a PNG file.
int main() {
    // Screen 2 x 1.5, the same shape as the 400 x 300 image, 1 in front of the eye.
    Camera camera(Vector(0, 0, -1), 2, 1.5, 1);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Image image(400, 300);

    camera.render(image, sphere);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";
    return 0;
}
