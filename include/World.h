//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_WORLD_H
#define WHITTED_WORLD_H

#include "AcceleratorInterface.h"
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

    World(std::unique_ptr<AcceleratorInterface> accelerator)
        : accelerator_{ std::move(accelerator) } {}

    bool Hit(const Ray& r, ShadeContext& context);
private:
    std::unique_ptr<AcceleratorInterface> accelerator_;
};


#endif //WHITTED_WORLD_H
