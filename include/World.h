//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_WORLD_H
#define WHITTED_WORLD_H

#include "Instance.h"
#include "Ray.h"
#include "ShadeContext.h"
#include "ShapeInterface.h"

#include <initializer_list>
#include <memory>
#include <vector>

class World {
public:
    World() = default;

    World(const std::initializer_list<Instance>& instances)
    {
        for (const Instance& instance : instances)
            world_.push_back(instance);
    }

    World(std::vector<Instance>& instances)
        : world_(instances) {}

    void AddShape(Instance instance);
    bool Hit(const Ray& r, ShadeContext& context);

private:
    std::vector<Instance> world_;
};


#endif //WHITTED_WORLD_H
