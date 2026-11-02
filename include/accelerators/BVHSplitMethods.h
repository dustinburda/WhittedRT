//
// Created by Dustin on 9/19/26.
//

#ifndef WHITTED_BVHSPLITMETHODS_H
#define WHITTED_BVHSPLITMETHODS_H

#include "BVH.h"

#include <span>

using ShapePartition = std::pair<std::span<InstancePtr>, std::span<InstancePtr>>;

ShapePartition RandomSplitAxisMethod(std::span<InstancePtr> shapes);
ShapePartition CentroidCountMedianSplit(std::span<InstancePtr> shapes);
ShapePartition CentroidSpatialMidpointSplit(std::span<InstancePtr> shapes);
ShapePartition SurfaceAreaHeuristic(std::span<InstancePtr> shapes);

ShapePartition Split(std::span<InstancePtr> shapes, BVH::SplitMethod split_method);

#endif //WHITTED_BVHSPLITMETHODS_H
