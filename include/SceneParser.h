//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "CameraInterface.h"
#include "Light.h"
#include "Sampler.h"
#include "Triangle.h"
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

    std::shared_ptr<Transformation> ParseRotation(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseReflection(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseTranslation(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseScale(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseTransformation(std::unique_ptr<XMLNode>& node);

    std::unique_ptr<CameraInterface> ParseCamera(std::unique_ptr<XMLNode>& node);

    Point3d ParseVertex (std::string point);
    std::shared_ptr<Triangle> ParseTriangle(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Instance> ParseShape(std::unique_ptr<XMLNode>& node);

    Color ParseColor(std::unique_ptr<XMLNode>& node, std::string attribute);

    std::shared_ptr<MaterialInterface> ParseMaterial(std::unique_ptr<XMLNode>& node);

    std::shared_ptr<Sampler> ParseSampler(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Light> ParsePointLight(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Light> ParseLight(std::unique_ptr<XMLNode>& node);


    struct {
        std::unordered_map<std::string, std::shared_ptr<Transformation>> name_transformation_;
        std::unordered_map<std::string, std::shared_ptr<Instance>> name_instance_;
        std::unordered_map<std::string, std::shared_ptr<MaterialInterface>> name_material_;
    } parsing_context_;

    XMLParser& xml_parser_;
};


#endif //SCENEPARSER_H
