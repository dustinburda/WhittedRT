//
// Created by Dustin on 12/22/24.
//

#ifndef BVH_H
#define BVH_H

#include <memory>
#include <optional>

#include "BoundingBox.h"
#include "Instance.h"

struct BVHNode {
public:
    BVHNode();

private:
    std::unique_ptr<BVHNode> left_;
    std::unique_ptr<BVHNode> right_;
    BoundingBox bounding_box_;

    std::optional<Instance> instance_;
    bool is_leaf_;

};

class BVH {
public:
    BVH(std::vector<Instance>& shapes) {}


private:
    void Build(std::vector<Instance>& shapes) {}

    BVHNode root;
};



#endif //BVH_H
