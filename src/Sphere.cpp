//
// Created by Advil on 11/6/2024.
//

#include "../include/Sphere.h"

#include <string>
#include <sstream>

bool Sphere::Hit(const Ray& r, ShadeContext& context) const {
    double a = Dot(r.Direction(), r.Direction());
    double b = 2 * Dot(r.Direction(), r.Origin() - center_);
    double c = Dot(r.Origin() - center_, r.Origin() - center_) - radius_ * radius_;

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return false;

    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    double hit_time = t1;
    if (t1 > context.t_max_ || t1 < context.t_min_)
    {
        hit_time = t2;
        if (t2 > context.t_max_ || t2 < context.t_min_)
            return false;
    }


    context.t_max_ = hit_time;
    context.point_ = r.At(hit_time);
    context.normal_ = NormalAt(r.At(hit_time));

    return true;
}

Normal<double, 3> Sphere::NormalAt(const Point<double, 3>& p) const {
    Vector<double, 3> diff = p - center_;
    return Normal<double, 3> {diff[0], diff[1], diff[2]};
}

std::string Sphere::toString() const {
    std::stringstream ss;

    ss << "Sphere: [";

    ss << center_.toString() << "\n";
    ss << "Radius: " << radius_ << "\n";

    ss << "]";

    return ss.str();
}