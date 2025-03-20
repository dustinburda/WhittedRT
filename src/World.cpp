//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"

#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/Material.h"
#include "../include/Sphere.h"

void World::AddShape(Instance instance)
{
    if(instance.Type() == InstanceType::Mesh) {
        // adds individual triangles from Mesh class
        instance.GetTriangles(instances_);
    }
    else {
        instances_.push_back(instance);
    }
}

void World::Build() {
    bvh_.Rebuild(instances_);
}

bool World::Hit(const Ray& r, ShadeContext& context)
{
    return bvh_.Hit(r, context);
}
