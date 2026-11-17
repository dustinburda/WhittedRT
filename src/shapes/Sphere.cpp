
//
// Created by Advil on 11/6/2024.
//

#include "../../include/shapes/Sphere.h"

#include "../../include/util/Util.h"

#include <cmath>
#include <string>
#include <sstream>

Sphere::Sphere() : ShapeInterface(ShapeType::Sphere) {}

bool Sphere::Hit(const Ray& r, ShadeContext& context) const {
    const auto center = Point3D{0.0, 0.0, 0.0};
    const auto radius = 1.0;

    double a = Dot(r.Direction(), r.Direction());
    double b = 2 * Dot(r.Direction(), r.Origin() - center);
    double c = Dot(r.Origin() - center, r.Origin() - center) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return false;

    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    double hit_time = 0.0;
    if (t1 < context.t_max_ && t1 > context.t_min_)
        hit_time = t1;
    else if (t2 < context.t_max_ && t2 > context.t_min_)
        hit_time = t2;
    else
        return false;

    Point<double, 3> hit_point = r.At(hit_time);

    context.t_max_ = hit_time;
    context.point_ = hit_point;
    context.normal_ = NormalAt(hit_point).value();

    // TODO: check this over
    auto phi = std::atan(context.point_[2] / -context.point_[1]) / (2 * pi);
    auto theta = std::acos(-context.point_[1]) / pi;
    context.uv_ = {phi, theta};

    return true;
}

std::optional<Normal<double, 3>> Sphere::NormalAt(const Point<double, 3>& p) const {
    Vector<double, 3> diff = p - Point3D {0.0, 0.0, 0.0};
    return Normal<double, 3> {diff[0], diff[1], diff[2]}.UnitNormal();
}

BoundingBox Sphere::BBox() const {
    Point3D min {-1, -1, -1};
    Point3D max {1, 1, 1};

    return BoundingBox {min, max};
}