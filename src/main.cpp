#include <iostream>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"
#include "render/camera.hpp"
#include "render/trace.hpp"

// Renders one sphere: one ray per pixel, then saves the image as a PNG.
int main() {
    // Screen 2 x 2, 1 in front of the eye. The sphere is 10 away with radius 5,
    // so it covers a bit more than half of the image.
    Camera camera(Vector(0, 0, -1), 2, 2, 1);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    Image image(512, 512);

    for (unsigned int row = 0; row < image.height(); row++) {
        for (unsigned int column = 0; column < image.width(); column++) {
            Ray ray = camera.rayThroughPixel(column, row, image.width(), image.height());
            image.setPixel(column, row, trace(ray, sphere));
        }
    }

    PngSaver saver;
    saver.save(image, "image.png");
    std::cout << "Saved image.png (" << image.width() << " x " << image.height() << ")\n";
    return 0;
}
