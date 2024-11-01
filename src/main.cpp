#include <iostream>


#include "../include/Canvas.h"
#include "../include/Vector.h"

static constexpr uint16_t HEIGHT = 250;
static constexpr uint16_t WIDTH = 500;

int main() {
    Canvas canvas (WIDTH, HEIGHT);

    canvas.SetColorAt({1,1,1}, 1, 1);
    canvas.SetColorAt({1,0,0}, 5, 10);
    canvas.SetColorAt({0,1,0}, 10, 5);
    canvas.SetColorAt({0,0,1}, 234, 435);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}