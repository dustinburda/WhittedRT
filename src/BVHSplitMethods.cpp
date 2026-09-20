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

int GetLargestSpatialExtent(std::span<Instance> shapes) {
    // TODO: Is this really defensive programming
    if (shapes.size() == 0)
        return 0;

    std::array<std::tuple<double, double>, 3> spatial_extents {{
        {std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest()},
        {std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest()},
        {std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest()},
    }};

    for (auto& shape : shapes) {
        const auto& centroid = shape.BBox().Centroid();

        for (std::size_t axis = 0; axis < 3; axis++) {
            auto& [extent_min, extent_max] = spatial_extents[axis];
            extent_min = std::min(extent_min, centroid[axis]);
            extent_max = std::max(extent_max, centroid[axis]);
        }
    };

    auto max_it = std::max_element(spatial_extents.begin(), spatial_extents.end(),
        [](const auto& extent1, const auto& extent2) {
        auto& [extent1_min, extent1_max] = extent1;
        auto& [extent2_min, extent2_max] = extent2;

        return std::abs(extent1_max - extent1_min) < std::abs(extent2_max - extent2_min);
    });

    return static_cast<int>(std::distance(spatial_extents.begin(), max_it));
}

ShapePartition CentroidCountMedianSplit ( [[ maybe_unused]] std::span<Instance> shapes) {
    int split_axis = GetLargestSpatialExtent(shapes);

    auto comparator = [&split_axis](Instance& i1, Instance i2) {
        return i1.BBox().Centroid()[split_axis] < i2.BBox().Centroid()[split_axis];
    };

    std::sort(shapes.begin(), shapes.end(), comparator);

    std::span s1 {shapes.begin(), shapes.begin() + shapes.size() / 2};
    std::span s2 {shapes.begin() + shapes.size() / 2, shapes.end() };

    return {s1, s2};
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