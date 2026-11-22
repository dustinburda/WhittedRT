//
// Created by Dustin on 11/21/26.
//

#include "../../include/renderer/Scene.h"
#include "../../include/parsers/ConfigParser.h"

std::pair<std::shared_ptr<MaterialInterface>, std::shared_ptr<Transformation>> GetMaterialTransformation(std::string name, std::unique_ptr<SceneData>& scene_data) {
    std::shared_ptr<MaterialInterface> material;
    if (scene_data->name_material_.contains(name))
        material = scene_data->name_material_[name];

    std::shared_ptr<Transformation> transformation;
    if (scene_data->name_transformation_.contains(name))
        transformation = scene_data->name_transformation_[name];

    return {material, transformation};
}

Scene::Scene(std::unique_ptr<SceneData>& scene_data)
    : camera_{std::move(scene_data->camera_)}, lights_{scene_data->lights_}
{
    for (auto&& [name, shape] : scene_data->name_shape_) {
        auto [material, transformation] = GetMaterialTransformation(name, scene_data);

        auto instance = std::make_shared<Instance>(transformation, shape, material);
        instances_.push_back(instance);
    }

    for (auto&& [name, mesh_data] : scene_data->name_meshdata_) {
        auto [material, transformation] = GetMaterialTransformation(name, scene_data);

        for(auto& face : mesh_data->faces_) {
            auto [vi1, vi2, vi3] = face;


            auto triangle = std::make_shared<Triangle>(
                                    Vertex{mesh_data->GetVertex(vi1), mesh_data->GetTextureCoordinate(vi1) },
                                    Vertex{mesh_data->GetVertex(vi2), mesh_data->GetTextureCoordinate(vi2) },
                                    Vertex{mesh_data->GetVertex(vi3), mesh_data->GetTextureCoordinate(vi3) });

            triangle->SetIsTextured(mesh_data->GetTextureCoordinate(vi1) != std::nullopt);

            auto instance = std::make_shared<Instance>(transformation, triangle, material);
        }
    }
}

void Scene::Initialize(Config& config) {
    accelerator_ = std::move(config.accelerator_);
    accelerator_->Build( {instances_.begin(), instances_.end()} );
}


bool Scene::Hit(const Ray& r, ShadeContext& context) const {
    return accelerator_->Hit(r, context);
}