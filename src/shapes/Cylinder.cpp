//
// Created by Dustin on 8/13/25.
//

#include "../../include/shapes/Cylinder.h"


UncappedCylinder::UncappedCylinder() : ShapeInterface(ShapeType::UncappedCylinder) {

}

std::optional<Normal<double, 3>> UncappedCylinder::NormalAt(const Point<double, 3>& p) const {
    // Not on surface
    if (std::abs(p[2]) > 1.0 || std::abs(p[0] * p[0] + p[1] * p[1] - 1.0) > epsilon)
        return std::nullopt;

    return Normal<double, 3> {p[0], p[1], 0.0};
}

bool UncappedCylinder::Hit(const Ray& r, ShadeContext& context) const {
    auto a = r.Direction()[0] * r.Direction()[0] + r.Direction()[1] * r.Direction()[1];
    auto b = 2 * (r.Direction()[0] * r.Origin()[0] + r.Direction()[1] * r.Origin()[1]);
    auto c = r.Origin()[0] * r.Origin()[0] + r.Origin()[1] * r.Origin()[1] - 1;

    auto discrminant = b * b - 4 * a * c;

    if (a == 0 || discrminant < 0)
        return false;

    auto t1 = (-b - std::sqrt(discrminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discrminant)) / (2 * a);

    double hit_time = 0.0;
    Point<double, 3> hit_point;
    if (t1 < context.t_max_ && t1 > context.t_min_ && std::abs(r.At(t1)[2]) <= 1.0) {
        hit_time = t1;
        hit_point = r.At(t1);
    } else if (t2 < context.t_max_ && t2 > context.t_min_ && std::abs(r.At(t2)[2]) <= 1.0) {
        hit_time = t2;
        hit_point = r.At(t2);
    } else {
        return false;
    }

    context.t_max_ = hit_time;
    context.point_ = hit_point;
    context.normal_ = NormalAt(context.point_).value();

    auto u=  (std::atan2(hit_point[1], hit_point[0]) + pi) / (2 * pi);
    auto v = (hit_point[2] + 1) / 2.0;
    context.uv_ = {u, v};

    return true;
}

BoundingBox UncappedCylinder::BBox() const {
    return BoundingBox{ Point3D{-1, -1, -1}, Point3D{1, 1, 1} };
}


std::vector<std::shared_ptr<ShapeInterface>> UncappedCylinder::Decompose() const {
    return {};
}

Cylinder::Cylinder() : ShapeInterface(ShapeType::Cylinder), cylinder_{}, cap1_{}, cap2_{} {
}

std::optional<Normal<double, 3>> Cylinder::NormalAt(const Point<double, 3>& p) const {
    for (auto& shape : Decompose()) {
        auto normal = shape->NormalAt(p);
        if (normal != std::nullopt)
            return normal;
    }

    return std::nullopt;
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
