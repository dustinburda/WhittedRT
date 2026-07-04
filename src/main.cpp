#include "../include/BoundingBox.h"
#include "../include/BVH.h"
#include "../include/ConfigParser.h"
#include "../include/Light.h"
#include "../include/ProjectiveCamera.h"
#include "../include/SceneParser.h"
#include "../include/Sphere.h"
#include "../include/ThreadPool.h"
#include "../include/World.h"
#include "../include/Vector.h"

#include <cstdlib>
#include <thread>

Color Trace(World& w, Ray& r, ShadeContext& context, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) {
    if(w.Hit(r, context))
    {
        return context.mat_->Shade(context, lights, ambient_intensity);
    }

    return {0.0, 0.0, 0.0};
}


void Render(CameraInterface* camera, Canvas& canvas, World& w, std::vector<std::shared_ptr<Light>>& lights, double ambient_intensity) {
    int num_threads = std::max(static_cast<int>(std::thread::hardware_concurrency()) - 2, 2);
    ThreadPool pool {num_threads};
    auto render = [&camera, &canvas, &lights, & ambient_intensity](World& w, int x_start, int chunk_x_size, int y_start, int chunk_y_size) {
        for(int y = y_start; y < y_start + chunk_y_size; y++)
            for(int x = x_start; x < x_start + chunk_x_size; x++) {
                auto rays = camera->GetRayAt(x, y);

                Color pixel_color;
                for (auto& ray : rays) {
                    ShadeContext context;
                    pixel_color += Trace(w, ray, context, lights, ambient_intensity);
                }
                pixel_color /= rays.size();

                canvas.SetColorAt(pixel_color, x, y);
            }
    };

    std::size_t chunk_x_size = canvas.Width() / std::min<std::size_t>(canvas.Width(), num_threads);
    std::size_t chunk_y_size = canvas.Height() /  std::min<std::size_t>(canvas.Height(), num_threads);

    for (std::size_t y = 0; y < canvas.Height(); y += std::min(chunk_y_size, canvas.Height() - y))
        for(std::size_t x = 0; x < canvas.Width(); x += std::min(chunk_x_size, canvas.Width() - x)) {
            std::thread t ( render, std::ref(w), x, chunk_x_size, y, chunk_y_size);
            pool.Add(std::move(t));
        }
}

class Renderer {
public:
private:
    Renderer() {

    }

    int num_threads;
};

class Scene {

};


int main(int argc, char** argv)
{
    Config config = ConfigParser::GetInstance().Parse("/config/Config.xml");

    // TODO: Get Render Time


    Canvas canvas {config.width_, config.height_};
    std::unique_ptr<CameraInterface> camera_ptr = std::make_unique<ProjectiveCamera>(config.width_, config.height_, 1.0);

    // TODO, encapsulate into scene class
    std::unique_ptr<World> world = nullptr;
    std::shared_ptr<Sampler> sampler = nullptr;
    std::vector<std::shared_ptr<Light>> lights;
    double ambient_intensity = 0.0;


    SceneParser::GetInstance().ParseScene(config.scene_description_path_, world, sampler, lights, ambient_intensity);

    camera_ptr->SetSampler(sampler);
    world->Build(); // Construct BVH
    Render(camera_ptr.get(), canvas, *world, lights, ambient_intensity);

    canvas.Flush(config.output_path_);
}