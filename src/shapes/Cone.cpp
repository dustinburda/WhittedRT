//
// Created by Dustin on 8/13/25.
//

#include "../../include/shapes/Cone.h"

Cone::Cone() : ShapeInterface(ShapeType::Cone) { }

std::optional<Normal<double, 3>> Cone::NormalAt([[ maybe_unused ]] const Point<double, 3>& p) const {
    if (p[2] > 1 || p[2] < -1)
        return std::nullopt;

    auto lhs = p[0] * p[0] + p[1] * p[1];
    auto rhs = (1 - p[2]) * (1 - p[2]) / 4.0;

    if (std::abs(lhs - rhs) > epsilon)
        return std::nullopt;

    // Normal at cone not defined
    if (std::abs(p[0]) < epsilon && std::abs(p[1]) < epsilon)
        return std::nullopt;

    return Normal<double, 3> {2 * p[0], 2 * p[1], 0.5 * (1 - p[2])}.UnitNormal();
}

bool Cone::Hit( [[ maybe_unused ]] const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    double a = 4 * r.Direction()[0] * r.Direction()[0] + 4 * r.Direction()[1] * r.Direction()[1] - r.Direction()[2] * r.Direction()[2];
    double b = 8 * r.Origin()[0] * r.Direction()[0] + 8 * r.Origin()[1] * r.Direction()[1] - 2 * r.Origin()[2] * r.Direction()[2] + 2 * r.Direction()[2];
    double c = 4 * r.Origin()[0] * r.Origin()[0] + 4 * r.Origin()[1] * r.Origin()[1]- r.Origin()[2] * r.Origin()[2] + 2 * r.Origin()[2] - 1;

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0 || a == 0)
        return false;

    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    if (a < 0)
        std::swap(t1, t2);

    double hit_time = 0.0;
    Point3D hit_point;
    if (t1 < context.t_max_ && t1 > context.t_min_ && NormalAt(r.At(t1)) != std::nullopt) {
        hit_time = t1;
        hit_point = r.At(t1);
    }
    else if (t2 < context.t_max_ && t2 > context.t_min_ && NormalAt(r.At(t2)) != std::nullopt) {
        hit_time = t2;
        hit_point = r.At(t2);
    }
    else
        return false;

    context.t_max_ = hit_time;
    context.point_ = hit_point;
    context.normal_ = NormalAt(hit_point).value();

    auto phi = (std::atan2(hit_point[1], hit_point[0]) + pi) / (2.0 * pi);
    auto theta = (hit_point[2] + 1.0) / 2.0;;
    context.uv_ = {phi, theta};

    return true;
}

BoundingBox Cone::BBox() const {
    return BoundingBox{Point3D {-1, -1, -1}, Point3D {1, 1, 1}};
}