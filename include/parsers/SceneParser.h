//
// Created by Dustin on 11/25/24.
//

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "../cameras/CameraInterface.h"
#include "../lights/LightInterface.h"
#include "../samplers/SamplerInterface.h"
#include "../shapes/Triangle.h"
#include "XMLParser.h"

#include <string>
#include <vector>

struct Scene {
    std::unique_ptr<AcceleratorInterface> accelerator_;
    std::shared_ptr<SamplerInterface> sampler_;
    std::unique_ptr<CameraInterface> camera_;
    std::vector<std::shared_ptr<LightInterface>> lights_;
    std::vector<InstancePtr> instances_;

    Scene() {
        accelerator_ = nullptr;
        sampler_ = nullptr;
        camera_ = nullptr;
        lights_ = {};
        instances_ = {};
    }

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;

    void Build();
    bool Hit(const Ray& r, ShadeContext& s) const;
};

class SceneParser {
public:
    static SceneParser& GetInstance() {
        static SceneParser p;

        return p;
    }

    std::unique_ptr<Scene> ParseScene(std::string path);
private:
    SceneParser();

    std::shared_ptr<Transformation> ParseRotation(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseReflection(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseTranslation(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseScale(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Transformation> ParseTransformation(std::unique_ptr<XMLNode>& node);

    std::unique_ptr<CameraInterface> ParseCamera(std::unique_ptr<XMLNode>& node);

    Point3D ParseVertex (std::string point);
    std::shared_ptr<Triangle> ParseTriangle(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<Instance> ParseShape(std::unique_ptr<XMLNode>& node);

    Color ParseColor(const XMLNode* node);

    std::shared_ptr<MaterialInterface> ParseMaterial(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<SamplerInterface> ParseSampler(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<LightInterface> ParsePointLight(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<LightInterface> ParseAmbientLight(std::unique_ptr<XMLNode>& node);
    std::shared_ptr<LightInterface> ParseLight(std::unique_ptr<XMLNode>& node);
    std::unique_ptr<AcceleratorInterface> ParseAccelerator(std::unique_ptr<XMLNode>& node);


    struct {
        std::unordered_map<std::string, std::shared_ptr<Transformation>> name_transformation_;
        std::unordered_map<std::string, std::shared_ptr<Instance>> name_instance_;
        std::unordered_map<std::string, std::shared_ptr<MaterialInterface>> name_material_;
        std::unordered_map<std::string, std::shared_ptr<SamplerInterface>> name_sampler_;
    } parsing_context_;

    XMLParser& xml_parser_;
};


#endif //SCENEPARSER_H
