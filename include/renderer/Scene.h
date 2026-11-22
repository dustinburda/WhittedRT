//
// Created by Dustin on 11/21/26.
//

#ifndef WHITTED_SCENE_H
#define WHITTED_SCENE_H


#include "../accelerators/AcceleratorInterface.h"
#include "../cameras/CameraInterface.h"
#include "../lights/LightInterface.h"
#include "../parsers/SceneParser.h"

#include <memory>
#include <vector>

struct Config;

class Scene {
public:
    Scene() = delete;
    Scene(std::unique_ptr<SceneData>& scene_data);

    void Initialize(Config& config);

    bool Hit(const Ray& r, ShadeContext& context) const;

public:
    std::unique_ptr<CameraInterface> camera_;
    std::vector<std::shared_ptr<LightInterface>> lights_;
    std::vector<std::shared_ptr<Instance>> instances_;
    std::unique_ptr<AcceleratorInterface> accelerator_;
};


#endif //WHITTED_SCENE_H
