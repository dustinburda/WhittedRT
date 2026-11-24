//
// Created by Dustin on 10/30/26.
//

#ifndef WHITTED_KDTREE_H
#define WHITTED_KDTREE_H

#include "AcceleratorInterface.h"

#include <memory>

class KDTreeNode {
public:
    explicit KDTreeNode(std::vector<InstancePtr> instances);
    KDTreeNode(std::unique_ptr<KDTreeNode> left, std::unique_ptr<KDTreeNode> right);

    bool Hit(const Ray& r, ShadeContext& s);

private:
    std::unique_ptr<KDTreeNode> left_;
    std::unique_ptr<KDTreeNode> right_;
    BoundingBox bounding_box_;

    std::vector<InstancePtr> instances_;
    bool is_leaf_;

};

#define KDTREE_SPLIT_METHODS \
    X(CycleSplitAxis) \
    X(RandomSplitAxis) \
    X(SurfaceAreaHeuristic)

class KDTree : public AcceleratorInterface {
public:
    enum class SplitMethod {
#define X(SplitMethod) SplitMethod,
        KDTREE_SPLIT_METHODS
#undef X
    };

    static SplitMethod StringToSplitMethod(std::string s) {
#define X(Method) \
if (#Method == s) \
return SplitMethod::Method; \
        KDTREE_SPLIT_METHODS
#undef X

        throw std::logic_error("Unknown SplitMethod: " + s);
    };

public:
    KDTree(std::size_t num_primitives_leaf, SplitMethod split_method);
    ~KDTree() override = default;

    bool Hit(const Ray& r, ShadeContext& s) override;
    void Build(std::vector<InstancePtr> instances) override;

private:
    std::unique_ptr<KDTreeNode> BuildRecursive(std::vector<InstancePtr> instances) const;

private:
    std::unique_ptr<KDTreeNode> root_;
    std::size_t num_primitives_leaf;
    SplitMethod split_method_;
};

#endif //WHITTED_KDTREE_H
