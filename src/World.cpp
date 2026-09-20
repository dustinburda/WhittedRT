//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"

void World::AddShape(Instance instance)
{
    for (auto& primitive_instance : instance.Decompose())
        instances_.push_back(primitive_instance);
}

void World::Build() {
    // TODO: World should have a choice of aggregate
    bvh_.Build(instances_, BVH::SplitMethod::RandomSplitAxis);
}

bool World::Hit(const Ray& r, ShadeContext& context)
{
    return bvh_.Hit(r, context);
}
