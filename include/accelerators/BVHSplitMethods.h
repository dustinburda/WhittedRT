//
// Created by Dustin on 9/19/26.
//

#ifndef WHITTED_BVHSPLITMETHODS_H
#define WHITTED_BVHSPLITMETHODS_H

#include "BVH.h"

#include <span>

using ShapePartition = std::pair<std::vector<InstancePtr>, std::vector<InstancePtr>>;

ShapePartition RandomSplitAxisMethod(std::vector<InstancePtr> shapes);
ShapePartition CentroidCountMedianSplit(std::vector<InstancePtr> shapes);
ShapePartition CentroidSpatialMidpointSplit(std::vector<InstancePtr> shapes);
ShapePartition SurfaceAreaHeuristic(std::vector<InstancePtr> shapes);

ShapePartition Split(std::vector<InstancePtr> shapes, BVH::SplitMethod split_method);

#endif //WHITTED_BVHSPLITMETHODS_H
