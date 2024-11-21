#include <iostream>
#include <memory>
#include <chrono>

#include "../include/Canvas.h"
#include "../include/Vector.h"
#include "../include/Point.h"
#include "../include/Normal.h"
#include "../include/Camera.h"
#include "../include/Sphere.h"

static constexpr uint16_t HEIGHT = 1080;
static constexpr uint16_t WIDTH = 1920;

/*
 * Add a World Class
 * Time core trace loop, make sure multithreading is on
 * Triangle
 * */

int main()
{
    auto flat_red_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    Sphere s ({0, 0, 10}, 3, flat_red_color);

    Canvas canvas {WIDTH, HEIGHT};
    Camera camera {WIDTH, HEIGHT, 1.0};

    #pragma omp parallel
    for (int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            auto ray = camera.GetRayAt(x, y);
            ShadeContext context;

            if(s.Hit(ray, context))
                canvas.SetColorAt(context.mat_->color_, x, y);

        }
    }

    std::cout << "Finished\n";
}