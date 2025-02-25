//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_WORLD_H
#define WHITTED_WORLD_H

#include "BVH.h"
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
            instances_.push_back(instance);
    }

    World(std::vector<Instance>& instances)
        : instances_(instances), bvh_{} {}

    void AddShape(Instance instance);
    bool Hit(const Ray& r, ShadeContext& context);
    void Build();

private:
    std::vector<Instance> instances_;
    BVH bvh_;
};


#endif //WHITTED_WORLD_H
