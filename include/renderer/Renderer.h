//
// Created by Dustin on 7/4/26.
//

#ifndef WHITTED_RENDERER_H
#define WHITTED_RENDERER_H

#include "../antialiasing/AntiAliasingInterface.h"
#include "../util/Color.h"
#include "ImagePlane.h"
#include "../materials/Material.h"
#include "Scene.h"
#include "../parsers/SceneParser.h"
#include "../renderer/ShadeContext.h"
#include "../util/TileQueue.h"

#include <thread>
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Initalize(Config& config);

    void Render(const Scene& scene, Canvas& canvas) ;


private:
    TileQueue GenerateTiles(const Canvas& canvas) const;
    void RenderTile(const Tile& t, const Scene& scene, Canvas& canvas) const ;

private:
    std::unique_ptr<AntiAliasingInterface> antialiasing_;

    std::vector<std::thread> threads_;
    std::size_t num_threads_;
};

#endif //WHITTED_RENDERER_H
