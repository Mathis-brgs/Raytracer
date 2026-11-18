#include<iostream>
#include "math/vector.hpp"
#include "geometry/ray.hpp"
#include "render/camera.hpp"
#include "geometry/sphere.hpp"
#include "colour/colour.hpp"


int main() {
    std:: cout <<"Hello, Raytracer! \n";

    // 1er parameter = O (origin), 2eme = D (direction)
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    // Sphere, centre et rayon
    Sphere sphere(Vector(0, 0, 9), 5);

    Colour colour(0, 0, 0);


    bool hit = sphere.hits(ray);
    if (hit) {
        std::cout << "Ray hit the sphere!\n";
        colour = Colour(1, 0, 0);
        Vector hitPoint = sphere.hitPoint(ray);
        std::cout << "Hit point: " << hitPoint.x() << ", " << hitPoint.y() << ", " << hitPoint.z() << "\n";
        std::cout << "Colour: (" << colour.r() << ", " << colour.g() << ", " << colour.b() << ")\n"; 
    } else {
        std::cout << "Ray missed the sphere.\n";
    }


return 0;
}