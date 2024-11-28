#include <chrono>
#include <filesystem>
#include <thread>
#include <vector>

#include "../include/Camera.h"
#include "../include/Canvas.h"
#include "../include/Mesh.h"
#include "../include/Sphere.h"
#include "../include/Threadpool.h"
#include "../include/World.h"

#include "../scenes/Scene1.h"

static constexpr uint16_t HEIGHT = 500;
static constexpr uint16_t WIDTH = 1000;

/*
 * Scene Parser [to make debugging and constructing scenes faster]
 * Normal Constructor from Vector
 * Color
 * Bounding Box
 * BVH
 * Tons of Unit Tests...
 * Matrix
 * Mutexes...
 * */


Color Trace(World& w, Ray& r, ShadeContext& context) {
    if(w.Hit(r, context))
        return context.mat_->color_;
    return {0.0, 0.0, 0.0};
}

int main()
{

    World w;

    Mesh m(std::filesystem::current_path().parent_path().string() + "/models/gourd.obj");
    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    std::vector<Triangle> mesh;
    m.GetTriangles(mesh, flat_green_color);

    for(auto& triangle : mesh)
    {
        auto points = triangle.Points();
        std::shared_ptr<Triangle> t = std::make_shared<Triangle>(triangle);
        w.AddShape(t);
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