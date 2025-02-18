//
// Created by Dustin on 1/30/25.
//

#ifndef WHITTED_BOUNDINGBOXTESTSCENE_H
#define WHITTED_BOUNDINGBOXTESTSCENE_H

#include <string>

#include "../include/Instance.h"
#include "../include/Sphere.h"

static std::string BoundingBoxTestScene(World& w)
{
    std::string name = "BoundingBoxTestScene";

    auto sphere_ptr = std::make_shared<Sphere>(Point<double, 3>{0.0, 0.0, 5.0}, 1.0);
    auto mat_ptr = std::make_shared<Material>(Color{1.0, 0.0, 0.0});
    auto sphere_instance = Instance {sphere_ptr, mat_ptr};

    w.AddShape(sphere_instance);

//    std::cout << "==================================================\n";
//    std::cout << sphere_ptr->toString();
//    std::cout << "\n";
//    std::cout << sphere_ptr->BBox().toString();
//    std::cout << "\n";
//    std::cout << "==================================================\n";

    return name;
}

#endif //WHITTED_BOUNDINGBOXTESTSCENE_H
