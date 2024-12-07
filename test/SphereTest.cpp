//
// Created by Dustin on 11/26/24.
//
#include <gtest/gtest.h>

#include "../include/Sphere.h"

TEST(SphereTest, Test1) {
    std::shared_ptr<ShapeInterface> s1  = std::make_shared<Sphere>(Point<double, 3>{-2, 0, 20}, 3, nullptr);
}
