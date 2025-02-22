//
// Created by Dustin on 12/22/24.
//

#ifndef BVH_H
#define BVH_H

#include "BoundingBox.h"
#include "Instance.h"

#include <memory>
#include <optional>

struct BVHNode {
public:
    explicit BVHNode(Instance instance);
    BVHNode(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right);

    bool Hit(const Ray& r, ShadeContext& context);

private:
    std::unique_ptr<BVHNode> left_;
    std::unique_ptr<BVHNode> right_;
    BoundingBox bounding_box_;

    std::optional<Instance> instance_;
    bool is_leaf_;

};

class BVH {
public:
    explicit BVH(std::vector<Instance>& shapes);
    bool Hit(const Ray& r, ShadeContext& s);

private:
    std::unique_ptr<BVHNode> Build(std::vector<Instance> shapes);

    std::unique_ptr<BVHNode> root_;
};



#endif //BVH_H


