//
// Created by Dustin on 10/30/26.
//

#ifndef WHITTED_KDTREE_H
#define WHITTED_KDTREE_H

#include "../AcceleratorInterface.h"

class KDTree : public AcceleratorInterface {
public:
    KDTree() = default;
    ~KDTree() override = default;

    virtual bool Hit(const Ray& r, ShadeContext& s) override;
    virtual void Build(std::vector<InstancePtr> instances) override;
};

#endif //WHITTED_KDTREE_H
