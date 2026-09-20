//
// Created by Dustin on 9/19/26.
//

#ifndef WHITTED_BVHSPLITMETHODS_H
#define WHITTED_BVHSPLITMETHODS_H

#include "BVH.h"

#include <span>

using ShapePartition = std::pair<std::span<Instance>, std::span<Instance>>;

ShapePartition RandomSplitAxisMethod(std::span<Instance> shapes);
ShapePartition CentroidCountMedianSplit(std::span<Instance> shapes);
ShapePartition CentroidSpatialMidpointSplit(std::span<Instance> shapes);
ShapePartition SurfaceAreaHeuristic(std::span<Instance> shapes);

ShapePartition Split(std::span<Instance> shapes, BVH::SplitMethod split_method);

#endif //WHITTED_BVHSPLITMETHODS_H
