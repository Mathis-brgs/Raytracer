#include <iostream>
#include <memory>
#include <string>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "light/light.hpp"
#include "material/lambert_material.hpp"
#include "math/vector.hpp"
#include "render/camera.hpp"

// Renders one red sphere lit by a white light, up and to the left, and saves it as a PNG file.
int main() {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    auto red = std::make_shared<LambertMaterial>(Colour(1, 0, 0));
    Sphere sphere(Vector(0, 0, 9), 5, red);
    Light light(Vector(-10, 10, -10), Colour(1, 1, 1));

    Image image = camera.render(sphere, light, 400, 300);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";
    return 0;
}
