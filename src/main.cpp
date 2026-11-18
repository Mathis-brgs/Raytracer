#include<iostream>
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "camera/camera.hpp"
#include "geometry/sphere.hpp"


int main() {
    std:: cout <<"Hello, Raytracer! \n";
    
    Ray ray(Vector(0, -1.0, 0), Vector(0, 1.0, 0));
    Sphere sphere(Vector(0, 9.0, 0), 5.0);
    Vector hitPoint = sphere.hitPoint(ray);
    std::cout << "Hit point: " << hitPoint.x() << ", " << hitPoint.y() << ", " << hitPoint.z() << "\n";

return 0;
}