//
// Created by Advil on 11/20/2024.
//

#include "../include/World.h"

bool World::Hit(const Ray& r, ShadeContext& context)
{
    return accelerator_->Hit(r, context);
}
