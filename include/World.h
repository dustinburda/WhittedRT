//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_WORLD_H
#define WHITTED_WORLD_H

#include "Ray.h"
#include "ShadeContext.h"
#include "ShapeInterface.h"

#include <initializer_list>
#include <memory>
#include <vector>

class World {
public:
    World() = default;

    World(const std::initializer_list<std::shared_ptr<ShapeInterface>>& shapes)
    {
        for (std::shared_ptr<ShapeInterface> shape_ptr : shapes)
            world_.push_back(std::move(shape_ptr));
    }

    World(std::vector<std::shared_ptr<ShapeInterface>>& shapes)
        : world_(shapes) {}

    void AddShape(std::shared_ptr<ShapeInterface> shape);
    bool Hit(const Ray& r, ShadeContext& context);

private:
    std::vector<std::shared_ptr<ShapeInterface>> world_;
};


#endif //WHITTED_WORLD_H
