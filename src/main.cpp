#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

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
 * Scene Parser [to make debugging and constructing scenes faster]
 * Normal Constructor from Vector
 * Color
 * Bounding Box
 * BVH
 * Tons of Unit Tests...
 * Matrix
 * */


Color Trace(World& w, Ray& r, ShadeContext& context) {
    if(w.Hit(r, context))
        return context.mat_->color_;
    return {0.0, 0.0, 0.0};
}

struct ThreadPool {
    ThreadPool()
        : num_threads_{std::thread::hardware_concurrency() - 4} { pool_.reserve(num_threads_); }
    ~ThreadPool() {
        for(auto&& thread : pool_)
            if(thread.joinable())
                thread.join();
    }
    void Add(std::thread&& t) {
        pool_.push_back(std::move(t));
    }

    size_t num_threads_;
    std::vector<std::thread> pool_;
};

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

    World w;
    for(int i = 0; i < 1000; i++) {
        w.AddShape(s6);
    }


    Canvas canvas {WIDTH, HEIGHT};
    Camera camera {WIDTH, HEIGHT, 1.0};

    std::size_t num_threads = std::thread::hardware_concurrency() - 2;
    ThreadPool pool;
    auto render = [&camera, &canvas](World& w, int x_start, int chunk_x_size, int y_start, int chunk_y_size) {
        for(int y = y_start; y < y_start + chunk_y_size; y++)
            for(int x = x_start; x < x_start + chunk_x_size; x++) {
                auto ray = camera.GetRayAt(x, y);
                ShadeContext context;
                canvas.SetColorAt(Trace(w, ray, context), x, y);
            }
    };

    std::size_t chunk_x_size = WIDTH / num_threads;
    std::size_t chunk_y_size = HEIGHT / num_threads;

    for (std::size_t y = 0; y < HEIGHT; y += chunk_y_size)
        for(std::size_t x = 0; x < WIDTH; x += chunk_x_size) {
            chunk_y_size = std::min(chunk_y_size, HEIGHT - y);
            chunk_x_size = std::min(chunk_x_size, WIDTH - x);

            std::thread t ( render, std::ref(w), x, chunk_x_size, y, chunk_y_size);
            pool.Add(std::move(t));
        }

    return 0;
}