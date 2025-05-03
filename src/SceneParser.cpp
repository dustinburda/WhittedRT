//
// Created by Dustin on 11/25/24.
//

#include "../include/Instance.h"
#include "../include/Mesh.h"
#include "../include/Plane.h"
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
        }
    }

    while (transformations.size()) {
        auto curr_transformation = transformations.top();
        transformations.pop();
        *transformation = (*transformation) * (*curr_transformation);
    }

    return transformation;
}

static std::shared_ptr<Instance> ParseShape(std::unique_ptr<XMLNode>& node) {
    std::string type = node->attributes_["type"];
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
        auto mesh_data = OBJParser::GetInstance().ParseOBJ(filename);

        shape_ptr = std::make_shared<Mesh>(mesh_data);
    } else if (type == "triangle") {
        instance_type = InstanceType::Triangle;
        shape_ptr = std::make_shared<Triangle>();
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


std::unique_ptr<World> SceneParser::ParseScene(std::filesystem::path path) {
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
    }

    auto world = std::make_unique<World>();
    for (auto [_, shape_ptr] : name_instance)
        world->AddShape(*shape_ptr);

    return world;
}

SceneParser::SceneParser() : xml_parser_{XMLParser::GetInstance()} {}