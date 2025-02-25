//
// Created by Dustin on 12/5/24.
//

#ifndef CESSNASCENE_H
#define CESSNASCENE_H

#include "../include/Instance.h"
#include "../include/Mesh.h"
#include "../include/OBJParser.h"
#include "../include/Sphere.h"
#include "../include/Util.h"
#include "../include/World.h"

static std::string CessnaScene(World& w) {
    std::string name = "cessna";

    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    auto sphere = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance = Instance { std::make_shared<Transformation>(Transformation::Translation(-10.5, 4.5, 8.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere, flat_green_color, InstanceType::Sphere };
    w.AddShape(sphere_instance);

    OBJParser parser;
    auto mesh_data = parser.ParseOBJ(std::filesystem::current_path().parent_path().string() + "/models/" + name + ".obj");

    auto m = std::make_shared<Mesh>(mesh_data);
    auto m_instance = Instance { std::make_shared<Transformation>(Transformation::Translation(0.0, 0.0, 9.0) * Transformation::Scale(1/3.0, 1/3.0, 1/3.0) * Transformation::RotationY(-pi/4)), m, flat_green_color, InstanceType::Mesh };
    w.AddShape(m_instance);

    w.Build();

    return name;
}


#endif //CESSNASCENE_H
