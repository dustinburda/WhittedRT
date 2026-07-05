//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "CameraInterface.h"
#include "Light.h"
#include "Sampler.h"
#include "XMLParser.h"
#include "World.h"

#include <string>
#include <vector>

struct Scene {
    std::unique_ptr<World> world_;
    std::shared_ptr<Sampler> sampler_;
    std::unique_ptr<CameraInterface> camera_;
    std::vector<std::shared_ptr<Light>> lights_;
    double ambient_intensity_;

    Scene() {
        world_ = nullptr;
        sampler_ = nullptr;
        lights_ = {};
        ambient_intensity_ = 0.0;
    }

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;
};

class SceneParser {
public:
    static SceneParser& GetInstance() {
        static SceneParser p;

        return p;
    }

    Scene ParseScene(std::string path);

private:
    SceneParser();

    XMLParser& xml_parser_;
};



#endif //SCENEPARSER_H
