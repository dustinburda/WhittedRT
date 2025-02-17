//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"

#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/Material.h"

void World::AddShape(Instance instance)
{
    world_.push_back(instance);
}

bool World::Hit(const Ray& r, ShadeContext& context)
{
    bool bHit = false;

    for(const Instance& instance : world_)
    {
        bHit |= instance.Hit(r, context);
    }

    return bHit;
}
