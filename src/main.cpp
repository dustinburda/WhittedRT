#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "../include/Camera.h"
#include "../include/Canvas.h"
#include "../include/Normal.h"
#include "../include/Plane.h"
#include "../include/Point.h"
#include "../include/Sphere.h"
#include "../include/Triangle.h"
#include "../include/World.h"

static constexpr uint16_t HEIGHT = 1080;
static constexpr uint16_t WIDTH = 1920;

/*
 * Time core trace loop, make sure multithreading is on
 * Scene Parser [to make debugging and constructing scenes faster]
 * Normal Constructor from Vector
 * Color
 * Mesh
 * Bounding Box
 * BVH
 * Tons of Unit Tests...
 * Matrix
 * */

int main()
{
    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    std::shared_ptr<Shape> s1  = std::make_shared<Sphere>(Point<double, 3>{-2, 0, 20}, 3, flat_green_color);

    auto flat_red_color = std::make_shared<Material>(Color {1.0, 0.0, 0.0});
    std::shared_ptr<Shape> s2  = std::make_shared<Sphere>(Point<double, 3>{2, 0, 25}, 3, flat_red_color);

    auto flat_blue_color = std::make_shared<Material>(Color{0.0, 0.0, 1.0});
    auto flat_gray_color = std::make_shared<Material>(Color{0.5, 0.5, 0.5});
    auto flat_purple_color = std::make_shared<Material>(Color{1.0, 0.0, 1.0});
    auto flat_yellow_color = std::make_shared<Material>(Color{1.0, 1.0, 0.0});
    auto flat_cyan_color = std::make_shared<Material>(Color{0.0, 1.0, 1.0});


    std::shared_ptr<Shape> s3 = std::make_shared<Plane>(Point<double, 3> {-4.0, 0.0, 0.0}, Normal<double, 3>{1.0, 0.0, 0.0}, flat_blue_color);
    std::shared_ptr<Shape> s4 = std::make_shared<Plane>(Point<double, 3> {0.0, -4.0, 0.0}, Normal<double, 3>{0.0, 1.0, 0.0}, flat_purple_color);
    std::shared_ptr<Shape> s5 = std::make_shared<Plane>(Point<double, 3> {0.0, 0.0, 30.0}, Normal<double, 3>{0.0, 0.0, 1.0}, flat_cyan_color);
    std::shared_ptr<Shape> s6 = std::make_shared<Triangle>(Point<double, 3> {0.0, 0.0, 0.0}, Point<double, 3> {1.0, 0.0, 0.0}, Point<double, 3> {0.5, 0.866, 0.0}, flat_yellow_color);

    World w {s6};

    Canvas canvas {WIDTH, HEIGHT};
    Camera camera {WIDTH, HEIGHT, 1.0};

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