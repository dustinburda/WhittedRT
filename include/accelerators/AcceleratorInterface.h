//
// Created by Dustin on 10/28/26.
//

#ifndef WHITTED_ACCELERATORINTERFACE_H
#define WHITTED_ACCELERATORINTERFACE_H

#include "../shapes/Instance.h"
#include "../math/Ray.h"
#include "../renderer/ShadeContext.h"

#include <memory>
#include <span>

// TODO: remove virtual call
class AcceleratorInterface {
public:
    virtual ~AcceleratorInterface() = default;

    virtual bool Hit(const Ray& r, ShadeContext& s) = 0;
    virtual void Build(std::span<InstancePtr> instances) = 0;
};

#endif //WHITTED_ACCELERATORINTERFACE_H
