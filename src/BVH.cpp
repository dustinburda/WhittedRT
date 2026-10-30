//
// Created by Dustin on 12/22/24.
//

#include <utility>

#include "../include/BVH.h"

#include "../include/BVHSplitMethods.h"
#include "../include/Util.h"

BVHNode::BVHNode(std::vector<Instance> instances)
    : left_{nullptr}, right_{nullptr}, instances_ {std::move(instances)}, is_leaf_{true}
{
    for (auto& instance : instances_) {
        bounding_box_ = Union(instance.BBox(), bounding_box_);
    }
}

BVHNode::BVHNode(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right)
    : left_ {std::move(left)}, right_ {std::move(right)}, bounding_box_{Union(left_->bounding_box_, right_->bounding_box_)}, instance_{std::nullopt}, is_leaf_{false} {}

bool BVHNode::Hit(const Ray& r, ShadeContext& context) {
    if (!bounding_box_.Hit(r, context))
        return false;

    if (is_leaf_) {
        bool hit = false;
        for (auto& instance : instances_) {
            hit |= instance.Hit(r, context);
        }
        return hit;
    } else {
        bool left = left_->Hit(r, context);
        bool right = right_->Hit(r, context);

        return left || right;
    }
}

BVH::BVH(std::size_t num_primitives_leaf, SplitMethod split_method)
    : root_{nullptr}, num_primitives_leaf_{num_primitives_leaf}, split_method_{split_method} {}

bool BVH::Hit(const Ray& r, ShadeContext& s) {
    if (root_ == nullptr)
        return false;

    return root_->Hit(r, s);
}

void BVH::Build(std::vector<Instance> shapes) {
    if (shapes.size() == 0)
        return;

    root_ = BuildRecursive(shapes);
}

std::unique_ptr<BVHNode> BVH::BuildRecursive(std::span<Instance> shapes) const {
    if (shapes.size() == 0)
        return nullptr;

    if (shapes.size() <= num_primitives_leaf_)
        return std::make_unique<BVHNode>(std::vector<Instance> { shapes.begin(), shapes.end()} );

    auto [s1, s2 ] = Split(shapes, split_method_);

    if (s1.empty() || s2.empty()) {
        return std::make_unique<BVHNode>(std::vector<Instance> { shapes.begin(), shapes.end()} );
    } else {
        auto left = BuildRecursive(s1);
        auto right = BuildRecursive(s2);

        return std::make_unique<BVHNode>(std::move(left), std::move(right));
    }
}