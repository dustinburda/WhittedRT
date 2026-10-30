//
// Created by Dustin on 10/28/26.
//

#ifndef WHITTED_ACCELERATORINTERFACE_H
#define WHITTED_ACCELERATORINTERFACE_H

#include "Instance.h"
#include "Ray.h"
#include "ShadeContext.h"

#include <memory>
#include <span>

// TODO: remove virtual call
class AcceleratorInterface {
public:
    virtual bool Hit(const Ray& r, ShadeContext& s) = 0;
    virtual void Build(std::vector<Instance> instances) = 0;
};

#endif //WHITTED_ACCELERATORINTERFACE_H
