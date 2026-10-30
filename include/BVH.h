//
// Created by Dustin on 12/22/24.
//

#ifndef BVH_H
#define BVH_H

#include "AcceleratorInterface.h"
#include "BoundingBox.h"
#include "Instance.h"

#include <span>
#include <memory>
#include <optional>

struct BVHNode {
public:
    explicit BVHNode(std::vector<Instance> instances);
    BVHNode(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right);

    bool Hit(const Ray& r, ShadeContext& context);

private:
    std::unique_ptr<BVHNode> left_;
    std::unique_ptr<BVHNode> right_;
    BoundingBox bounding_box_;

    std::vector<Instance> instances_;
    bool is_leaf_;

};

#define SPLIT_METHODS \
    X(RandomSplitAxis) \
    X(CentroidCountMedianSplit) \
    X(CentroidSpatialMidpointSplit) \
    X(SurfaceAreaHeuristic)

class BVH : public AcceleratorInterface {
public:
    enum class SplitMethod {
#define X(SplitMethod) SplitMethod,
        SPLIT_METHODS
#undef X
    };

    static SplitMethod StringToSplitMethod(std::string s) {
#define X(Method) \
if (#Method == s) \
return SplitMethod::Method;
        SPLIT_METHODS
#undef X

        throw std::logic_error("Unknown SplitMethod: " + s);
    }

public:
    BVH(std::size_t num_primitives_leaf, SplitMethod split_method);
    bool Hit(const Ray& r, ShadeContext& s) override;
    void Build(std::vector<Instance> shapes) override;
private:
    std::unique_ptr<BVHNode> BuildRecursive(std::span<Instance> shapes) const;

private:
    std::unique_ptr<BVHNode> root_;
    std::size_t num_primitives_leaf_;
    SplitMethod split_method_;
};

#endif //BVH_H


