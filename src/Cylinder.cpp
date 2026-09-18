//
// Created by Dustin on 8/13/25.
//

#include "../include/Cylinder.h"

Cylinder::Cylinder() : ShapeInterface(ShapeType::Cylinder) {

}

Normal<double, 3> Cylinder::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    return Normal<double, 3> {};
}

bool Cylinder::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    return false;
}

BoundingBox Cylinder::BBox() const {
    return BoundingBox{};
}
