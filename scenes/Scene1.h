//
// Created by Dustin on 11/27/24.
//

#ifndef SCENE1_H
#define SCENE1_H



#include <iostream>
#include <memory>

#include "../include/Normal.h"
#include "../include/Plane.h"
#include "../include/Point.h"
#include "../include/Triangle.h"
#include "../include/World.h"

static void Scene1(World& w)
{
    auto flat_green_color = std::make_shared<Material>(Color {0.0, 1.0, 0.0});
    std::shared_ptr<Shape> s1  = std::make_shared<Sphere>(Point<double, 3>{-2, 0, 20}, 3, flat_green_color);

    auto flat_red_color = std::make_shared<Material>(Color {1.0, 0.0, 0.0});
    std::shared_ptr<Shape> s2  = std::make_shared<Sphere>(Point<double, 3>{2, 0, 25}, 3, flat_red_color);

    auto flat_blue_color = std::make_shared<Material>(Color{0.0, 0.0, 1.0});
    auto flat_gray_color = std::make_shared<Material>(Color{0.5, 0.5, 0.5});
    auto flat_purple_color = std::make_shared<Material>(Color{1.0, 0.0, 1.0});
    auto flat_yellow_color = std::make_shared<Material>(Color{1.0, 1.0, 0.0});
    auto flat_cyan_color = std::make_shared<Material>(Color{0.0, 1.0, 1.0});


    std::shared_ptr<Shape> s3 = std::make_shared<Plane>(Point<double, 3> {-4.0, 0.0, 0.0}, Normal<double, 3>{1.0, 0.0, 0.0}, flat_blue_color);
    std::shared_ptr<Shape> s4 = std::make_shared<Plane>(Point<double, 3> {0.0, -4.0, 0.0}, Normal<double, 3>{0.0, 1.0, 0.0}, flat_purple_color);
    std::shared_ptr<Shape> s5 = std::make_shared<Plane>(Point<double, 3> {0.0, 0.0, 30.0}, Normal<double, 3>{0.0, 0.0, 1.0}, flat_cyan_color);
    std::shared_ptr<Shape> s6 = std::make_shared<Triangle>(Point<double, 3> {0.0, 0.0, 0.0}, Point<double, 3> {1.0, 0.0, 0.0}, Point<double, 3> {0.5, 0.866, 0.0}, flat_yellow_color);


    for(int i = 0; i < 1000; i++) {
        w.AddShape(s6);
    }
}

#endif //SCENE1_H