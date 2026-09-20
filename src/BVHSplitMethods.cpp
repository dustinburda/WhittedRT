//
// Created by Dustin on 9/19/26.
//

#include "../include/BVHSplitMethods.h"


ShapePartition RandomSplitAxisMethod(std::span<Instance> shapes) {

    int split_axis = RandomInt(0, 2);

    auto comparator = [&split_axis](const Instance& i1, const Instance& i2) {
        return i1.BBox().Min()[split_axis] < i2.BBox().Min()[split_axis];
    };

    std::sort(shapes.begin(), shapes.end(), comparator);

    std::span<Instance> s1 {shapes.begin(), shapes.begin() + shapes.size() / 2};
    std::span<Instance> s2 {shapes.begin() + shapes.size() / 2, shapes.end()};

    return {s1, s2};
};


ShapePartition CentroidCountMedianSplit ( [[ maybe_unused]] std::span<Instance> shapes) {
    return {};
};

ShapePartition CentroidSpatialMedianSplit ( [[ maybe_unused]]  std::span<Instance> shapes) {
    return {};
};

ShapePartition SurfaceAreaHeuristic ( [[ maybe_unused]]  std::span<Instance> shapes) {
    return {};
};

ShapePartition Split(std::span<Instance> shapes, BVH::SplitMethod split_method) {

    switch (split_method) {
        case BVH::SplitMethod::RandomSplitAxis:
            return RandomSplitAxisMethod(shapes);
        case BVH::SplitMethod::CentroidCountMedianSplit:
            return CentroidCountMedianSplit(shapes);
        case BVH::SplitMethod::CentroidSpatialMedianSplit:
            return CentroidSpatialMedianSplit(shapes);
        case BVH::SplitMethod::SurfaceAreaHeuristic:
            return SurfaceAreaHeuristic(shapes);
        default:
            throw std::logic_error("Unsupported split method");
    }

}