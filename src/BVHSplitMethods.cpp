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

double GetCentroidMidpoint(std::span<Instance> shapes, int split_axis) {
    auto min = std::numeric_limits<double>::max();
    auto max = std::numeric_limits<double>::lowest();

    for (auto& shape : shapes) {
        min = std::min(min , shape.BBox().Centroid()[split_axis]);
        max = std::max(max , shape.BBox().Centroid()[split_axis]);
    }

    return (min + max) * 0.5;
}

ShapePartition CentroidCountMedianSplit (std::span<Instance> shapes) {
    int split_axis = GetLargestSpatialExtent(shapes);

    auto comparator = [&split_axis](const Instance& i1, const Instance& i2) {
        return i1.BBox().Centroid()[split_axis] < i2.BBox().Centroid()[split_axis];
    };

    std::sort(shapes.begin(), shapes.end(), comparator);

    std::span s1 {shapes.begin(), shapes.begin() + shapes.size() / 2};
    std::span s2 {shapes.begin() + shapes.size() / 2, shapes.end() };

    return {s1, s2};
};

ShapePartition CentroidSpatialMidpointSplit (std::span<Instance> shapes) {
    int split_axis = GetLargestSpatialExtent(shapes);

    double centroid_midpoint = GetCentroidMidpoint(shapes, split_axis);

    // TODO: What if the partition returns shape.begin()?
    auto it = std::partition(shapes.begin(), shapes.end(), [&centroid_midpoint, &split_axis](const Instance& i1) {
        return i1.BBox().Centroid()[split_axis] < centroid_midpoint;
    });

    std::span s1 {shapes.begin(), it};
    std::span s2 {it, shapes.end()};

    return {s1, s2};
};

std::pair<double, std::span<Instance>::iterator> ComputeCheapestSAHSplit(std::span<Instance> shapes) {
    int split_axis = GetLargestSpatialExtent(shapes);

    auto comparator = [&split_axis](const Instance& i1, const Instance& i2) {
        return i1.BBox().Centroid()[split_axis] < i2.BBox().Centroid()[split_axis];
    };

    std::sort(shapes.begin(), shapes.end(), comparator);

    double min_split_cost = std::numeric_limits<double>::max();
    std::span<Instance>::iterator min_split_it = shapes.begin();
    for (std::size_t i = 0; i < shapes.size() - 1; i++) {
        BoundingBox b1 = shapes[0].BBox();
        for (std::size_t j = 0; j <= i; j++) {
            b1 = Union(b1, shapes[j].BBox());
        }

        BoundingBox b2 = shapes[i + 1].BBox();
        for (std::size_t j = i + 1; j < shapes.size(); j++) {
            b2 = Union(b2, shapes[j].BBox());
        }

        double curr_split_cost = (b1.SurfaceArea() * static_cast<double>(i + 1)
                               + b2.SurfaceArea() * static_cast<double>(shapes.size() - i - 1)) / (Union(b1, b2).SurfaceArea());

        if ( curr_split_cost < min_split_cost) {
            min_split_cost = curr_split_cost;
            min_split_it = std::next(shapes.begin(), i + 1 );
        }
    }

    return {min_split_cost, min_split_it};
}

ShapePartition SurfaceAreaHeuristic (std::span<Instance> shapes) {
    auto leaf_cost = static_cast<double>(shapes.size());
    auto split_cost = 0.125; // Initial cost

    auto [min_split_cost, min_split_it] = ComputeCheapestSAHSplit(shapes);

    split_cost += min_split_cost;

    if (leaf_cost < split_cost) {
        return {shapes, {}};
    } else {
        std::span<Instance> s1 {shapes.begin(), min_split_it};
        std::span<Instance> s2 {min_split_it , shapes.end()};

        return {s1, s2};
    }
};

ShapePartition Split(std::span<Instance> shapes, BVH::SplitMethod split_method) {

    switch (split_method) {
        case BVH::SplitMethod::RandomSplitAxis:
            return RandomSplitAxisMethod(shapes);
        case BVH::SplitMethod::CentroidCountMedianSplit:
            return CentroidCountMedianSplit(shapes);
        case BVH::SplitMethod::CentroidSpatialMidpointSplit:
            return CentroidSpatialMidpointSplit(shapes);
        case BVH::SplitMethod::SurfaceAreaHeuristic:
            return SurfaceAreaHeuristic(shapes);
        default:
            throw std::logic_error("Unsupported split method");
    }

}