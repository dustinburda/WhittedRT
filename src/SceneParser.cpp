//
// Created by Dustin on 11/25/24.
//

#include "../include/HammersleySampler.h"
#include "../include/JitteredSampler.h"
#include "../include/Instance.h"
#include "../include/Light.h"
#include "../include/PointLight.h"
#include "../include/Mesh.h"
#include "../include/Plane.h"
#include "../include/RandomSampler.h"
#include "../include/RegularSampler.h"
#include "../include/Sampler.h"
#include "../include/SceneParser.h"
#include "../include/ShapeInterface.h"
#include "../include/Sphere.h"
#include "../include/Transformation.h"
#include "../include/Triangle.h"
#include "../include/Util.h"


#include <sstream>
#include <string>

#include "../include/OrthographicCamera.h"
#include "../include/ProjectiveCamera.h"

std::shared_ptr<Transformation> SceneParser::ParseRotation(std::unique_ptr<XMLNode>& node) {
    std::string axis = node->attributes_["axis"];
    double degrees = std::stod(node->attributes_["val"]);
    double radians = degrees * pi / 180.0;

    std::shared_ptr<Transformation> t = nullptr;
    if (axis == "x") {
        t = std::make_shared<Transformation>(Transformation::RotationX(radians));
    } else if (axis == "y") {
        t = std::make_shared<Transformation>(Transformation::RotationY(radians));
    } else if (axis == "z") {
        t = std::make_shared<Transformation>(Transformation::RotationZ(radians));
    }

    return t;
}

std::shared_ptr<Transformation> SceneParser::ParseReflection(std::unique_ptr<XMLNode>& node) {
    std::string axis = node->attributes_["axis"];

    std::shared_ptr<Transformation> t = nullptr;
    if (axis == "x") {
        t = std::make_shared<Transformation>(Transformation::ReflectionX());
    } else if (axis == "y") {
        t = std::make_shared<Transformation>(Transformation::ReflectionY());
    } else if (axis == "z") {
        t = std::make_shared<Transformation>(Transformation::ReflectionZ());
    }

    return t;
}

std::shared_ptr<Transformation> SceneParser::ParseTranslation(std::unique_ptr<XMLNode>& node) {
    double x = (node->attributes_.count("x") > 0.0) ? std::stod(node->attributes_["x"]) : 0.0;
    double y = (node->attributes_.count("y") > 0.0) ? std::stod(node->attributes_["y"]) : 0.0;
    double z = (node->attributes_.count("z") > 0.0) ? std::stod(node->attributes_["z"]) : 0.0;

    double x_translation = x;
    double y_translation = y;
    double z_translation = z;

    return std::make_shared<Transformation>(Transformation::Translation(x_translation, y_translation, z_translation));
}

std::shared_ptr<Transformation> SceneParser::ParseScale(std::unique_ptr<XMLNode>& node) {
    double x_scale = (node->attributes_.count("x") > 0) ? std::stod(node->attributes_["x"]) : 0.0;
    double y_scale = (node->attributes_.count("y") > 0) ? std::stod(node->attributes_["y"]) : 0.0;
    double z_scale = (node->attributes_.count("z") > 0) ? std::stod(node->attributes_["z"]) : 0.0;

    return std::make_shared<Transformation>(Transformation::Scale(x_scale, y_scale, z_scale));
}

std::shared_ptr<Transformation> SceneParser::ParseTransformation(std::unique_ptr<XMLNode>& node) {
    auto transformation = std::make_shared<Transformation>(Transformation::Identity());
    // Order of transformations matters
    std::stack<std::shared_ptr<Transformation>> transformations;

    // TODO: Use Child Value
    for (auto& child : node->children_) {
        std::shared_ptr<Transformation> curr_transformation = nullptr;
        if (child->tag_ == "rotation") {
            transformations.push(ParseRotation(child));
        } else if (child->tag_ == "reflection") {
            transformations.push(ParseReflection(child));
        } else if (child->tag_ == "translation") {
            transformations.push(ParseTranslation(child));
        } else if (child->tag_ == "scale") {
            transformations.push(ParseScale(child));
        } else {
            transformations.push(std::make_shared<Transformation>(Transformation::Identity()));
        }
    }

    // TODO: Get rid of this stupid loop
    while (transformations.size()) {
        auto curr_transformation = transformations.top();
        transformations.pop();
        *transformation = (*transformation) * (*curr_transformation);
    }

    return transformation;
}

// TODO: Get rid of this diabolically stupid function
Point3d SceneParser::ParseVertex (std::string point) {
    std::stringstream ss {point};
    std::string token;

    double x, y, z;

    std::getline(ss, token, ',');
    x = std::stod(token);

    std::getline(ss, token, ',');
    y = std::stod(token);

    std::getline(ss, token, ',');
    z = std::stod(token);

    return Point3d {x, y, z};
}

std::shared_ptr<Triangle> SceneParser::ParseTriangle(std::unique_ptr<XMLNode>& node) {
    auto vertex1 { ParseVertex(node->attributes_["point1"]) };
    auto vertex2 { ParseVertex(node->attributes_["point2"]) };
    auto vertex3 { ParseVertex(node->attributes_["point3"]) };

    return std::make_shared<Triangle>(vertex1, vertex2, vertex3);
}

std::shared_ptr<Instance> SceneParser::ParseShape(std::unique_ptr<XMLNode>& node) {
    std::string type = node->attributes_["type"];

    // Handle case where transformation is not provided
    std::string transformation_name = node->attributes_["transformation"];
    std::string material_name = node->attributes_["material"];

    auto material_ptr = parsing_context_.name_material_[material_name];
    auto transformation_ptr = parsing_context_.name_transformation_[transformation_name]; // Confusing, fix this
    std::shared_ptr<ShapeInterface> shape_ptr = nullptr;
    InstanceType instance_type;

    if (type == "sphere") {
        instance_type = InstanceType::Sphere;
        shape_ptr = std::make_shared<Sphere>();
    } else if (type == "plane") {
        instance_type = InstanceType::Plane;
        shape_ptr = std::make_shared<Plane>();
    } else if (type == "mesh") {
        instance_type = InstanceType::Mesh;

        std::string filename = node->attributes_["filename"];
        auto mesh_data = OBJParser::GetInstance().ParseOBJ( "../models/" + filename);

        shape_ptr = std::make_shared<Mesh>(mesh_data);
    } else if (type == "triangle") {
        instance_type = InstanceType::Triangle;
        shape_ptr = ParseTriangle(node);
    }

    return std::make_shared<Instance>(transformation_ptr, shape_ptr, material_ptr, instance_type);
}

Color SceneParser::ParseColor(std::unique_ptr<XMLNode>& node, std::string attribute) {
    std::stringstream s { node->attributes_[attribute] };

    double r, b, g;
    std::string token;
    std::getline(s, token, ',');
    r = std::stod(token);

    std::getline(s, token, ',');
    g = std::stod(token);

    std::getline(s, token, ',');
    b = std::stod(token);

    return Color {r, g, b};
}

std::shared_ptr<MaterialInterface> SceneParser::ParseMaterial(std::unique_ptr<XMLNode>& node) {
    std::string type = node->attributes_["type"];

    std::shared_ptr<MaterialInterface> mat = nullptr;

    if (type == "simple_phong") {
        mat = std::make_shared<SimplePhongMaterial>(ParseColor(node, "ka"),
                                                    ParseColor(node, "kd"),
                                                    ParseColor(node, "ks"),
                                                    std::stod(node->attributes_["power"]));
    } else {
        mat = std::make_shared<BlackMaterial>();
    }

    return mat;
}

std::shared_ptr<Sampler> SceneParser::ParseSampler(std::unique_ptr<XMLNode>& node) {
    // TODO: handle case where there is no sampler node

    auto num_samples = std::stoi(node->attributes_["samples"]);
    auto sampler_type = node->attributes_["type"];

    std::shared_ptr<Sampler> sampler = nullptr;

    if (sampler_type == "hammersley") {
        sampler = std::make_shared<HammersleySampler>(num_samples);
    } else if (sampler_type == "jittered") {
        sampler = std::make_shared<JitteredSampler>(num_samples);
    } else if (sampler_type == "regular") {
        sampler = std::make_shared<RegularSampler>(num_samples);
    } else if (sampler_type == "random") {
        sampler = std::make_shared<RandomSampler>(num_samples);
    }

    return sampler;
}

template<typename T>
T Parse3D(const XMLNode* node) {
    auto x = std::stod(node->attributes_.at("x"));
    auto y = std::stod(node->attributes_.at("y"));
    auto z = std::stod(node->attributes_.at("z"));

    return T {x, y, z};
}

std::unique_ptr<CameraInterface> SceneParser::ParseCamera(std::unique_ptr<XMLNode>& node) {
    std::unique_ptr<CameraInterface> camera = nullptr;

    auto type = node->attributes_["type"];

    auto origin = Parse3D<Point3d>(node->ChildNode("origin"));
    auto lookat = Parse3D<Vec3d>(node->ChildNode("lookat"));
    auto up = Parse3D<Vec3d>(node->ChildNode("up"));
    auto fov = std::stoi(node->ChildNode("fov")->value_);

    if (type == "projective") {
        camera = std::make_unique<ProjectiveCamera>(origin, lookat, up, fov);
    } else if (type == "orthographic") {
        camera = std::make_unique<OrthographicCamera>(origin, lookat, up, fov);
    } else {
        throw std::logic_error ("Uknown Camera Type");
    }

    return camera;
}

std::shared_ptr<Light> SceneParser::ParsePointLight(std::unique_ptr<XMLNode>& node) {
    double r, g, b;
    std::stringstream s { node->attributes_["color"] };

    std::string token;
    std::getline(s, token, ',');
    r = std::stod(token);

    std::getline(s, token, ',');
    g = std::stod(token);

    std::getline(s, token, ',');
    b = std::stod(token);

    auto color = Color{r,g,b};
    auto position = ParseVertex( node->attributes_["position"]); // TODO: THIS IS BS, REDO SCHEMA HERE
    auto intensity = std::stof(node->attributes_["intensity"]);

    return std::make_shared<PointLight>(position, intensity, color);
}

std::shared_ptr<Light> SceneParser::ParseLight(std::unique_ptr<XMLNode>& node) {

    std::shared_ptr<Light> light = nullptr;
    if (node->attributes_["type"] == "point") {
        light = ParsePointLight(node);
    }

    return light;
}

Scene SceneParser::ParseScene(std::string path) {
    std::ifstream file {path};
    auto file_size = std::filesystem::file_size(path);

    std::string src;
    src.resize(file_size);
    file.read(src.data(), file_size);

    auto node = xml_parser_.Parse(src);

    Scene scene;

    // TODO: Use ChildValue
    for (auto& child : node->children_) {
        if (child->tag_ == "transformation")
            parsing_context_.name_transformation_[child->attributes_["name"]] = ParseTransformation(child);
        else if (child->tag_ == "shape")
            parsing_context_.name_instance_[child->attributes_["name"]] = ParseShape(child);
        else if (child->tag_ == "material")
            parsing_context_.name_material_[child->attributes_["name"]] = ParseMaterial(child);
        else if (child->tag_ == "antialiasing")
            scene.sampler_ = ParseSampler(child);
        else if (child->tag_ == "camera")
            scene.camera_ = std::move(ParseCamera(child));
        else if (child->tag_ == "light") {
            if (child->attributes_["type"] == "ambient") {
                scene.ambient_intensity_ = std::stod(child->attributes_["intensity"]);
            } else {
                scene.lights_.push_back(ParseLight(child));
            }
        }
    }


    // TODO: Questionable. Shouldn't a scene parser just parse the scene?
    scene.world_ = std::make_unique<World>();
    for (auto [_, shape_ptr] : parsing_context_.name_instance_)
        scene.world_->AddShape(*shape_ptr);
    scene.world_->Build();

    return scene;
}

SceneParser::SceneParser() : xml_parser_{XMLParser::GetInstance()} {}