//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_WORLD_H
#define WHITTED_WORLD_H

#include "Ray.h"
#include "ShadeContext.h"
#include "Shape.h"

#include <initializer_list>
#include <memory>
#include <vector>

class World {
public:
    World() = default;

    World(const std::initializer_list<std::shared_ptr<Shape>>& shapes)
    {
        for (std::shared_ptr<Shape> shape_ptr : shapes)
            world_.push_back(std::move(shape_ptr));
    }

    World(std::vector<std::shared_ptr<Shape>>& shapes)
        : world_(shapes) {}

    void AddShape(std::shared_ptr<Shape> shape);
    void AddMesh(std::string name, std::shared_ptr<Material> mat);
    bool Hit(const Ray& r, ShadeContext& context);

private:
    std::vector<std::shared_ptr<Shape>> world_;
};


#endif //WHITTED_WORLD_H
