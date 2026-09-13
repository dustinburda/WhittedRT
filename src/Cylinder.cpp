//
// Created by Dustin on 8/13/25.
//

#include "../include/Cylinder.h"


Normal<double, 3> NormalAt(const Point<double, 3>& p) const {
    return Normal<double, 3> {};
}

bool Hit(const Ray& r, ShadeContext& context) const {
    return false;
}

BoundingBox BBox() const {
    return BoundingBox{};
}
