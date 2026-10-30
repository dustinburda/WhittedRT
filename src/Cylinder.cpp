//
// Created by Dustin on 8/13/25.
//

#include "../include/Cylinder.h"


UncappedCylinder::UncappedCylinder() : ShapeInterface(ShapeType::UncappedCylinder) {

}

Normal<double, 3> UncappedCylinder::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    return Normal<double, 3> {};
}

bool UncappedCylinder::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    return false;
}

BoundingBox UncappedCylinder::BBox() const {
    return BoundingBox{};
}




Cylinder::Cylinder() : ShapeInterface(ShapeType::Cylinder) {

}

Normal<double, 3> Cylinder::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    // TODO: Solve this
    return Normal<double, 3> {};
}

bool Cylinder::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    bool hit = false;
    for (auto& shape : {cylinder_, cap1_, cap2_}) {
        hit |= shape.hit(r, context);
    }

    return hit;
}

BoundingBox Cylinder::BBox() const {
    return Union(Union(cap1_.BBox(), cap2_.BBox()), cylinder_.BBox());
}
