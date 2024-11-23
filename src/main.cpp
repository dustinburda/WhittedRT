#include <chrono>
#include <iostream>
#include <memory>

#include "../include/Camera.h"
#include "../include/Canvas.h"
#include "../include/Normal.h"
#include "../include/Plane.h"
#include "../include/Point.h"
#include "../include/Sphere.h"
#include "../include/Vector.h"
#include "../include/World.h"

static constexpr uint16_t HEIGHT = 1080;
static constexpr uint16_t WIDTH = 1920;

/*
 * Time core trace loop, make sure multithreading is on
 * Triangle
 * Normal Constructor from Vector
 * Color
 * */

int main()
{
    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    std::shared_ptr<Shape> s1  = std::make_shared<Sphere>(Point<double, 3>{-2, 0, 20}, 3, flat_green_color);

    auto flat_red_color = std::make_shared<Material>(Color {1.0, 0.0, 0.0});
    std::shared_ptr<Shape> s2  = std::make_shared<Sphere>(Point<double, 3>{2, 0, 25}, 3, flat_red_color);

//    auto flat_blue_color = std::make_shared<Material>(Color{0.0, 0.0, 1.0});
//    std::shared_ptr<Shape> s3 = std::make_shared<Plane>()

    auto flat_gray_color = std::make_shared<Material>(Color{0.5, 0.5, 0.5});


    World w {s1, s2};

    Canvas canvas {WIDTH, HEIGHT};
    Camera camera {WIDTH, HEIGHT, 1.0};

    #pragma omp parallel
    for (int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            auto ray = camera.GetRayAt(x, y);
            ShadeContext context;


            if(w.Hit(ray, context))
                canvas.SetColorAt(context.mat_->color_, x, y);

        }
    }

    std::cout << "Finished\n";
}