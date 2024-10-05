#include <iostream>


#include "../include/Canvas.h"
#include "../include/Vector.h"

static constexpr uint16_t HEIGHT = 250;
static constexpr uint16_t WIDTH = 500;

int main() {
    Canvas canvas (WIDTH, HEIGHT);

    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, 2.0, 3.0, 4.0 };

    auto vec3 = vec1 + vec2;
    auto vec4 = vec3 - vec2;


    canvas.SetColorAt({1,1,1}, 1, 1);
    canvas.SetColorAt({1,0,0}, 5, 10);
    canvas.SetColorAt({0,1,0}, 10, 5);
    canvas.SetColorAt({0,0,1}, 234, 435);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
