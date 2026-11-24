//
// Created by Dustin on 11/4/26.
//

#include "../../include/accelerators/KDTree.h"
#include "../../include/accelerators/KDTreeSplitMethods.h"

KDTreeNode::KDTreeNode(std::vector<InstancePtr> instances)
    : left_{nullptr}, right_{nullptr}, bounding_box_{}, instances_{instances}, is_leaf_{true}
{

}

KDTreeNode::KDTreeNode(std::unique_ptr<KDTreeNode> left, std::unique_ptr<KDTreeNode> right)
    : left_{std::move(left)}, right_{std::move(right)}, is_leaf_{false}
{

}

bool KDTreeNode::Hit(const Ray& r, ShadeContext& s) {
    if (!bounding_box_.Hit(r, s))
        return false;

    if (is_leaf_) {
        bool hit = false;
        for (const auto& instance : instances_) {
            hit |= instance->Hit(r, s);
        }

        return hit;
    } else {
        auto t_left = left_->bounding_box_.HitAt(r, s);
        auto t_right = right_->bounding_box_.HitAt(r, s);

        if (!t_left && !t_right)
            return false;

        if (!t_left)
            return right_->Hit(r, s);

        if (!t_right)
            return left_->Hit(r, s);

        std::unique_ptr<KDTreeNode>& closer = (*t_left < *t_right) ? left_ : right_;
        [[ maybe_unused ]] auto closer_t = std::min(*t_left,*t_right);
        std::unique_ptr<KDTreeNode>& further = (*t_left >= *t_right) ? left_ : right_;
        auto further_t = std::max(*t_left, *t_right);

        auto hit  = closer->Hit(r, s);
        if (!hit || s.t_max_ >= further_t)
            hit |= further->Hit(r, s);

        return hit;
    }
}

KDTree::KDTree(std::size_t num_primitives_leaf, SplitMethod split_method)
    : num_primitives_leaf{num_primitives_leaf}, split_method_{split_method}
{

}

bool KDTree::Hit(const Ray& r, ShadeContext& s) {
    return root_->Hit(r, s);
}

void KDTree::Build(std::vector<InstancePtr> instances) {
    root_ = BuildRecursive(instances);
}

std::unique_ptr<KDTreeNode> KDTree::BuildRecursive(std::vector<InstancePtr> instances) const {
    if (instances.empty())
        return nullptr;

    if (instances.size() <= num_primitives_leaf) {
        return std::make_unique<KDTreeNode>(instances);
    } else {
        auto [s1, s2] = Split(instances);

        auto left = BuildRecursive(s1);
        auto right = BuildRecursive(s2);

        return std::make_unique<KDTreeNode>(std::move(left), std::move(right));
    }
}
