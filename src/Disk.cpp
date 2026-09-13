//
// Created by Dustin on 9/13/26.
//

#include "../include/Disk.h"


Normal<double, 3> Disk::NormalAt( [[ maybe_unused]] const Point<double, 3>& p) const {
    return normal_;
}

bool Disk::Hit( [[ maybe_unused]] const Ray& r, [[ maybe_unused]] ShadeContext& context) const {
    return true;
}

BoundingBox Disk::BBox() const {
    return BoundingBox {};
}