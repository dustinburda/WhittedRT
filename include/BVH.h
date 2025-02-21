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
    explicit BVHNode(Instance instance)
        : left_{nullptr}, right_{nullptr}, bounding_box_{instance.BBox()}, instance_ {instance}, is_leaf_{true} {}

    BVHNode(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right)
        : left_ {std::move(left)}, right_ {std::move(right)}, bounding_box_{Union(left->bounding_box_, right->bounding_box_)}, instance_{std::nullopt}, is_leaf_{false} {}

    bool Hit(const Ray& r, ShadeContext& context) {
        if (!bounding_box_.Hit(r, context))
            return false;

        if (is_leaf_) {
            return instance_->Hit(r, context);
        }

        bool left = left_->Hit(r, context);
        bool right = left_->Hit(r, context);

        return left || right;
    }

private:
    std::unique_ptr<BVHNode> left_;
    std::unique_ptr<BVHNode> right_;
    BoundingBox bounding_box_;

    std::optional<Instance> instance_;
    bool is_leaf_;

};

class BVH {
public:
    explicit BVH(std::vector<Instance>& shapes) {
        root_ = Build(shapes);
    }

    bool Hit(const Ray& r, ShadeContext& s) {
        return root_->Hit(r, s);
    }
private:
    std::unique_ptr<BVHNode> Build(std::vector<Instance> shapes) {
        if (shapes.size() == 1) {
            return std::make_unique<BVHNode>(shapes[0]);
        }

        // TODO: replace basic comparator with Surface Area Heuristic
        [[maybe_unused]] auto comparator = [](Instance i1, Instance i2) {
            // TODO: implement
            return true;
        };

        std::sort(shapes.begin(), shapes.end(), comparator);

        std::vector<Instance> s1 {shapes.begin(), shapes.begin() + shapes.size() / 2};
        std::vector<Instance> s2 {shapes.begin() + shapes.size() / 2, shapes.end()};

        auto left = Build(s1);
        auto right = Build(s2);

        return std::make_unique<BVHNode>(std::move(left), std::move(right));
    }

    std::unique_ptr<BVHNode> root_;
};



#endif //BVH_H


