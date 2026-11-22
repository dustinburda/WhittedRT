//
// Created by Dustin on 10/30/26.
//

#ifndef WHITTED_KDTREE_H
#define WHITTED_KDTREE_H

#include "AcceleratorInterface.h"

#include <memory>

class KDTreeNode {
public:
    explicit KDTreeNode(std::span<InstancePtr> instances);
    KDTreeNode(std::unique_ptr<KDTreeNode> left, std::unique_ptr<KDTreeNode> right);

    bool Hit(const Ray& r, ShadeContext& s);

private:
    std::unique_ptr<KDTreeNode> left;
    std::unique_ptr<KDTreeNode> right;

    bool is_leaf_;

};

class KDTree : public AcceleratorInterface {
public:
    KDTree(int num_primitives_leaf);
    ~KDTree() override = default;

    bool Hit(const Ray& r, ShadeContext& s) override;
    void Build(std::span<InstancePtr> instances) override;
private:
    std::unique_ptr<KDTree> root_;
    int num_primitives_leaf;
};

#endif //WHITTED_KDTREE_H
