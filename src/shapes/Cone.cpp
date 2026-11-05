//
// Created by Dustin on 8/13/25.
//

#include "../../include/shapes/Cone.h"

std::optional<Normal<double, 3>> UncappedCone::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    return std::nullopt;
}

bool UncappedCone::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    return false;
}

BoundingBox UncappedCone::BBox() const {
    return BoundingBox{Point3D {-1, -1, -1}, Point3D {1, 1, 1}};
}

std::vector<std::shared_ptr<ShapeInterface>> UncappedCone::Decompose() const {
    return {};
}


std::optional<Normal<double, 3>> Cone::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    return std::nullopt;
}

bool Cone::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    return false;
}

BoundingBox Cone::BBox() const {
    return BoundingBox{Point3D {-1, -1, -1}, Point3D {1, 1, 1}};
}

std::vector<std::shared_ptr<ShapeInterface>> Cone::Decompose() const {
    return {};
}
