//
// Created by Dustin on 2/24/25.
//

#ifndef WHITTED_BVHTESTSCENE_H
#define WHITTED_BVHTESTSCENE_H

#include "../include/BVH.h"
#include "../include/Mesh.h"
#include "../include/OBJParser.h"
#include "../include/Sphere.h"
#include "../include/World.h"

static std::string BVHScene(World& w) {
    std::string name = "BVHScene";

    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    auto flat_red_color = std::make_shared<Material>(Color {1.0, 0.0, 0.0});
    auto flat_blue_color = std::make_shared<Material>(Color {0.0, 0.0, 1.0});
    auto flat_purple_color = std::make_shared<Material>(Color {1.0, 0.0, 1.0});
    auto flat_cyan_color = std::make_shared<Material>(Color {0.0, 1.0, 1.0});

    auto sphere1 = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance1 = Instance { std::make_shared<Transformation>(Transformation::Translation(0.5, 0.5, 2.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere1, flat_green_color };
    w.AddShape(sphere_instance1);

    auto sphere2 = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance2 = Instance { std::make_shared<Transformation>(Transformation::Translation(-6.5, 3.5, 2.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere2, flat_red_color };
    w.AddShape(sphere_instance2);

    auto sphere3 = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance3 = Instance { std::make_shared<Transformation>(Transformation::Translation(6.5, -2.5, 2.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere3, flat_blue_color };
    w.AddShape(sphere_instance3);

    auto sphere4 = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance4 = Instance { std::make_shared<Transformation>(Transformation::Translation(6.5, 3.5, 2.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere4, flat_purple_color };
    w.AddShape(sphere_instance4);

    auto sphere5 = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 4.0}, 1.0);
    auto sphere_instance5 = Instance { std::make_shared<Transformation>(Transformation::Translation(-6.5, -3.5, 2.0) * Transformation::Scale(2.0, 2.0, 1.0)) , sphere5, flat_cyan_color };
    w.AddShape(sphere_instance5);

    return name;
}


#endif //WHITTED_BVHTESTSCENE_H
