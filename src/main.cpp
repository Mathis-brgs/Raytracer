#include <iostream>
#include <memory>
#include <string>

#include "colour/colour.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "light/light.hpp"
#include "material/lambert_material.hpp"
#include "math/vector.hpp"
#include "render/camera.hpp"
#include "scene/scene.hpp"

// Renders a sphere on a grey floor, lit by a white light up and to the right, and saves it as a PNG file.
int main() {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    Scene scene(Light(Vector(10, 10, -8), Colour(1, 1, 1)));
    auto colour = std::make_shared<LambertMaterial>(Colour(0.3, 0.7, 0.8));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, colour));
    // The floor touches the bottom of the sphere (centre y = 0, radius 5).
    auto grey = std::make_shared<LambertMaterial>(Colour(0.8, 0.8, 0.8));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), grey));

    Image image = camera.render(scene, 400, 300);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";
    return 0;
}
