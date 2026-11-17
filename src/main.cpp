#include<iostream>
#include "vector.hpp"

int main() {
    std:: cout <<"Hello, Raytracer! \n";

    Vector v1(1.0, 2.0,3.0);
    Vector v2(4.0, 5.0, 6.0);
    Vector v3 = v1.add(v2);
    Vector v4 = v1.subtract(v2);

return 0;
}