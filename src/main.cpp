#include <iostream>


#include "../include/Canvas.h"
#include "../include/Vector.h"
#include "../include/Point.h"
#include "../include/Normal.h"
#include "../include/Camera.h"
#include "../include/Sphere.h"

static constexpr uint16_t HEIGHT = 5;
static constexpr uint16_t WIDTH = 5;


int main()
{

    Canvas canvas {WIDTH, HEIGHT};
    Camera camera {WIDTH, HEIGHT, 1.0};

    for (int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            auto ray = camera.GetRayAt(x, y);
            Sphere s;

        }
    }

    std::cout << "Hello World\n";
}