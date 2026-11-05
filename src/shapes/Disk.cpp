//
// Created by Dustin on 9/13/26.
//

#include "../../include/shapes/Disk.h"

Disk::Disk() : ShapeInterface(ShapeType::Disk) {}

std::optional<Normal<double, 3>> Disk::NormalAt(const Point<double, 3>& p) const {
    if (std::abs(p[2]) > epsilon || std::abs(p[0] * p[0] + p[1] * p[1] - 1.0) < epsilon)
        return std::nullopt;

    return Normal<double, 3> {0.0, 0.0, 1.0};
}

bool Disk::Hit( const Ray& r, ShadeContext& context) const {
    if (std::abs(r.Direction()[2]) < epsilon)
        return false;

    double hit_time = (-r.Origin()[2]) / (r.Direction()[2]);
    if (hit_time < context.t_min_ || hit_time > context.t_max_)
        return false;

    auto hit_point = r.At(hit_time);
    if (DistanceSquared(hit_point, Point3D {0, 0, 0}) > 1)
        return false;

    context.t_max_ = hit_time;
    context.point_ = hit_point;
    context.normal_ = NormalAt(hit_point).value();

    return true;
}

BoundingBox Disk::BBox() const {
    return BoundingBox { Point3D {-1, -1, -0.1}, Point3D {1, 1, 0.1}};
}

std::vector<std::shared_ptr<ShapeInterface>> Disk::Decompose() const {
    return {};
}