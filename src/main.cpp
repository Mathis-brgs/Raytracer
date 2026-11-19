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
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, 400, 300);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";
    return 0;
}
