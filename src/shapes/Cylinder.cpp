//
// Created by Dustin on 8/13/25.
//

#include "../../include/shapes/Cylinder.h"


UncappedCylinder::UncappedCylinder() : ShapeInterface(ShapeType::UncappedCylinder) {

}

std::optional<Normal<double, 3>> UncappedCylinder::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    return Normal<double, 3> {};
}

bool UncappedCylinder::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    return false;
}

BoundingBox UncappedCylinder::BBox() const {
    return BoundingBox{};
}


std::vector<std::shared_ptr<ShapeInterface>> UncappedCylinder::Decompose() const {
    return {};
}

Cylinder::Cylinder() : ShapeInterface(ShapeType::Cylinder), cylinder_{}, cap1_{}, cap2_{} {
}

std::optional<Normal<double, 3>> Cylinder::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    // TODO: Solve this
    return Normal<double, 3> {};
}

bool Cylinder::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    bool hit = false;
    for (auto& shape : Decompose()) {
        hit |= shape->Hit(r, context);
    }

    return hit;
}

BoundingBox Cylinder::BBox() const {
    return Union(Union(cap1_->BBox(), cap2_->BBox()), cylinder_->BBox());
}

std::vector<std::shared_ptr<ShapeInterface>> Cylinder::Decompose() const {
    return {cylinder_, cap1_, cap2_};
}
