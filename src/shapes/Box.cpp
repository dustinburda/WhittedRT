//
// Created by Dustin on 1/26/26.
//

#include "../../include/shapes/Box.h"

Box::Box() : ShapeInterface(ShapeType::Box) {

}

Normal<double, 3> Box::NormalAt( [[ maybe_unused ]] const Point<double, 3>& p) const {
    return Normal<double, 3> {};
}
bool Box::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {

}

BoundingBox Box::BBox() const {
    return BoundingBox{Point3D {-1, -1, -1}, Point3D {1, 1, 1}};
}