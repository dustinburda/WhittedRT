//
// Created by Dustin on 12/22/24.
//

#include "../include/BVH.h"

#include "../include/Util.h"

BVHNode::BVHNode(Instance instance)
    : left_{nullptr}, right_{nullptr}, bounding_box_{instance.BBox()}, instance_ {instance}, is_leaf_{true} {}

BVHNode::BVHNode(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right)
    : left_ {std::move(left)}, right_ {std::move(right)}, bounding_box_{Union(left->bounding_box_, right->bounding_box_)}, instance_{std::nullopt}, is_leaf_{false} {}

bool BVHNode::Hit(const Ray& r, ShadeContext& context) {
    if (!bounding_box_.Hit(r, context))
        return false;

    if (is_leaf_) {
        return instance_->Hit(r, context);
    }

    bool left = left_->Hit(r, context);
    bool right = right_->Hit(r, context);

    return left || right;
}


BVH::BVH(std::vector<Instance>& shapes) {
    root_ = Build(shapes);
}

bool BVH::Hit(const Ray& r, ShadeContext& s) {
    return root_->Hit(r, s);
}

std::unique_ptr<BVHNode> BVH::Build(std::vector<Instance> shapes) {
    if (shapes.size() == 1) {
        return std::make_unique<BVHNode>(shapes[0]);
    }

    int split_axis = RandomInt(1, 3);

    // TODO: replace basic comparator with Surface Area Heuristic
    auto comparator = [&split_axis](Instance i1, Instance i2) {
        return i1.BBox().Min()[split_axis] < i2.BBox().Min()[split_axis];
    };

    std::sort(shapes.begin(), shapes.end(), comparator);

    std::vector<Instance> s1 {shapes.begin(), shapes.begin() + shapes.size() / 2};
    std::vector<Instance> s2 {shapes.begin() + shapes.size() / 2, shapes.end()};

    auto left = Build(s1);
    auto right = Build(s2);

    return std::make_unique<BVHNode>(std::move(left), std::move(right));
}