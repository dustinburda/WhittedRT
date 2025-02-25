//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"

#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/Material.h"

void World::AddShape(Instance instance)
{
    instances_.push_back(instance);
}

bool World::Hit(const Ray& r, ShadeContext& context)
{
    bvh_.Rebuild(instances_);
    return bvh_.Hit(r, context);
}
