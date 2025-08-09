#include "../include/BoundingBox.h"
#include "../include/BVH.h"
#include "../include/ProjectiveCamera.h"
#include "../include/Sphere.h"
#include "../include/Threadpool.h"
#include "../include/World.h"
#include "../include/SceneParser.h"

#include <cstdlib>
#include <thread>

static constexpr uint16_t HEIGHT = 500;
static constexpr uint16_t WIDTH = 1000;

Color Shade(ShadeContext& context) {
    return context.mat_->color_;
}

Color Trace(World& w, Ray& r, ShadeContext& context) {
    if(w.Hit(r, context))
         return Shade(context);
    return {0.0, 0.0, 0.0};
}


void Render(CameraInterface* camera, Canvas& canvas, World& w) {
    std::size_t num_threads = std::thread::hardware_concurrency() - 2;
    ThreadPool pool;
    auto render = [&camera, &canvas](World& w, int x_start, int chunk_x_size, int y_start, int chunk_y_size) {
        for(int y = y_start; y < y_start + chunk_y_size; y++)
            for(int x = x_start; x < x_start + chunk_x_size; x++) {
                auto rays = camera->GetRayAt(x, y);
                ShadeContext context;

                Color pixel_color;
                for (auto& ray : rays) {
                    pixel_color += Trace(w, ray, context);
                }
                pixel_color /= rays.size();

                canvas.SetColorAt(pixel_color, x, y);
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
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        throw std::logic_error("Can only pass a single parameter!");
    }

    std::string scene_description_file_name = argv[1];
    auto scene_description_file_path = "../scenes/" + scene_description_file_name + ".xml";
    std::ifstream scene_description_file {scene_description_file_path};

    if (!scene_description_file.is_open()) {
        throw std::logic_error("Scene description file: \"" + scene_description_file_name + ".xml" +  "\" does not exist.");
    }

    Canvas canvas {WIDTH, HEIGHT};

    ProjectiveCamera camera {WIDTH, HEIGHT, 1.0};
    std::unique_ptr<World> world = nullptr;
    std::shared_ptr<Sampler> sampler = nullptr;

    SceneParser::GetInstance().ParseScene(scene_description_file_path, world, sampler);

    camera.SetSampler(sampler);
    world->Build(); // Construct BVH
    Render(&camera, canvas, *world);

    canvas.Flush(scene_description_file_name + ".ppm");
}