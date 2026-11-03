
//
// Created by Advil on 11/6/2024.
//

#include "../../include/shapes/Sphere.h"

#include "../../include/util/Util.h"

#include <cmath>
#include <string>
#include <sstream>

Sphere::Sphere() : ShapeInterface(ShapeType::Sphere), center_{0,0,0}, radius_{1.0} {}
Sphere::Sphere(const Point<double, 3>& center, double radius)
    : ShapeInterface(ShapeType::Sphere), center_{center}, radius_{radius} {}

bool Sphere::Hit(const Ray& r, ShadeContext& context) const {
    double a = Dot(r.Direction(), r.Direction());
    double b = 2 * Dot(r.Direction(), r.Origin() - center_);
    double c = Dot(r.Origin() - center_, r.Origin() - center_) - radius_ * radius_;

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


    context.t_max_ = hit_time;
    context.point_ = r.At(hit_time);
    context.normal_ = NormalAt(r.At(hit_time)).value();

    // TODO: check this over
    auto phi = std::atan(context.point_[2] / -context.point_[1]) / (2 * pi);
    auto theta = std::acos(-context.point_[1]) / pi;
    context.uv_ = {phi, theta};

    return true;
}

std::optional<Normal<double, 3>> Sphere::NormalAt(const Point<double, 3>& p) const {
    Vector<double, 3> diff = p - center_;
    return Normal<double, 3> {diff[0], diff[1], diff[2]};
}

BoundingBox Sphere::BBox() const {
    Point3D min {center_[0] - radius_, center_[1] - radius_, center_[2] - radius_};
    Point3D max {center_[0] + radius_, center_[1] + radius_, center_[2] + radius_};

    return BoundingBox {min, max};
}

std::vector<std::shared_ptr<ShapeInterface>> Sphere::Decompose() const {
    return {};
}