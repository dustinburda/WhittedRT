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

static std::unordered_map<std::string, std::shared_ptr<Transformation>> name_transformation;
static std::unordered_map<std::string, std::shared_ptr<Instance>> name_instance;
static std::unordered_map<std::string, std::shared_ptr<Material>> name_material;

static std::shared_ptr<Transformation> ParseRotation(std::unique_ptr<XMLNode>& node) {
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

static std::shared_ptr<Transformation> ParseReflection(std::unique_ptr<XMLNode>& node) {
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

static std::shared_ptr<Transformation> ParseTranslation(std::unique_ptr<XMLNode>& node) {
    double x_translation = (node->attributes_.count("x") > 0) ? std::stod(node->attributes_["x"]) : 0.0;
    double y_translation = (node->attributes_.count("y") > 0) ? std::stod(node->attributes_["y"]) : 0.0;
    double z_translation = (node->attributes_.count("z") > 0) ? std::stod(node->attributes_["z"]) : 0.0;

    return std::make_shared<Transformation>(Transformation::Translation(x_translation, y_translation, z_translation));
}

static std::shared_ptr<Transformation> ParseScale(std::unique_ptr<XMLNode>& node) {
    double x_scale = (node->attributes_.count("x") > 0) ? std::stod(node->attributes_["x"]) : 0.0;
    double y_scale = (node->attributes_.count("y") > 0) ? std::stod(node->attributes_["y"]) : 0.0;
    double z_scale = (node->attributes_.count("z") > 0) ? std::stod(node->attributes_["z"]) : 0.0;

    return std::make_shared<Transformation>(Transformation::Scale(x_scale, y_scale, z_scale));
}

static std::shared_ptr<Transformation> ParseTransformation(std::unique_ptr<XMLNode>& node) {
    auto transformation = std::make_shared<Transformation>(Transformation::Identity());
    // Order of transformations matters
    std::stack<std::shared_ptr<Transformation>> transformations;

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
        }
    }

    while (transformations.size()) {
        auto curr_transformation = transformations.top();
        transformations.pop();
        *transformation = (*transformation) * (*curr_transformation);
    }

    return transformation;
}

static Point3d ParsePoint (std::string point) {
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

static std::shared_ptr<Triangle> ParseTriangle(std::unique_ptr<XMLNode>& node) {
    auto vertex1 { ParsePoint(node->attributes_["point1"]) };
    auto vertex2 { ParsePoint(node->attributes_["point2"]) };
    auto vertex3 { ParsePoint(node->attributes_["point3"]) };

    return std::make_shared<Triangle>(vertex1, vertex2, vertex3);
}

static std::shared_ptr<Instance> ParseShape(std::unique_ptr<XMLNode>& node) {
    std::string type = node->attributes_["type"];

    // Handle case where transformation is not provided
    std::string transformation_name = node->attributes_["transformation"];
    std::string material_name = node->attributes_["material"];

    auto material_ptr = name_material[material_name];
    auto transformation_ptr = name_transformation[transformation_name]; // Confusing, fix this
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

static std::shared_ptr<Material> ParseMaterial(std::unique_ptr<XMLNode>& node) {
    double r, g, b;
    std::stringstream s { node->attributes_["color"] };

    std::string token;
    std::getline(s, token, ',');
    r = std::stod(token);

    std::getline(s, token, ',');
    g = std::stod(token);

    std::getline(s, token, ',');
    b = std::stod(token);

    return std::make_shared<Material>(Color {r, g, b});
}

static std::shared_ptr<Sampler> ParseSampler(std::unique_ptr<XMLNode>& node) {
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

static std::shared_ptr<Light> ParsePointLight(std::unique_ptr<XMLNode>& node) {
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
    auto position = ParsePoint( node->attributes_["position"]);
    auto intensity = std::stof(node->attributes_["intensity"]);

    return std::make_shared<PointLight>(position, intensity, color);
}

static std::shared_ptr<Light> ParseLight(std::unique_ptr<XMLNode>& node) {

    std::shared_ptr<Light> light = nullptr;
    if (node->attributes_["type"] == "point") {
        light = ParsePointLight(node);
    }

    return light;
}

void SceneParser::ParseScene(std::filesystem::path path, std::unique_ptr<World>& world, std::shared_ptr<Sampler>& sampler, std::vector<std::shared_ptr<Light>>& lights) {
    std::ifstream file {path};
    auto file_size = std::filesystem::file_size(path);

    std::string src;
    src.resize(file_size);
    file.read(src.data(), file_size);

    auto node = xml_parser_.Parse(src);

    for (auto& child : node->children_) {
        if (child->tag_ == "transformation")
            name_transformation[child->attributes_["name"]] = ParseTransformation(child);
        else if (child->tag_ == "shape")
            name_instance[child->attributes_["name"]] = ParseShape(child);
        else if (child->tag_ == "material")
            name_material[child->attributes_["name"]] = ParseMaterial(child);
        else if (child->tag_ == "antialiasing")
            sampler = ParseSampler(child);
        else if (child->tag_ == "light")
            lights.push_back(ParseLight(child));
    }

    world = std::make_unique<World>();
    for (auto [_, shape_ptr] : name_instance)
        world->AddShape(*shape_ptr);
}

SceneParser::SceneParser() : xml_parser_{XMLParser::GetInstance()} {}