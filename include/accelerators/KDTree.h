//
// Created by Dustin on 10/30/26.
//

#ifndef WHITTED_KDTREE_H
#define WHITTED_KDTREE_H

#include "AcceleratorInterface.h"

#include <memory>

class KDTreeNode {

};

class KDTree : public AcceleratorInterface {
public:
    KDTree() = default;
    ~KDTree() override = default;

    bool Hit(const Ray& r, ShadeContext& s) override;
    void Build(std::span<InstancePtr> instances) override;
private:
    std::unique_ptr<KDTree> root_;
};

#endif //WHITTED_KDTREE_H
