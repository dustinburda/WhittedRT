//
// Created by Advil on 11/6/2024.
//

#include "../include/Plane.h"

#include <string>
#include <sstream>

Normal<double, 3> Plane::NormalAt(const Point<double, 3>& p) const
{
    return normal_;
}

bool Plane::Hit(const Ray& r, ShadeContext& context) const
{
    // Ray parallel to Plane
    if (std::abs(Dot(r.Direction(), normal_)) <= epsilon)
        return false;

    double hit_time = Dot(normal_, point_- r.Origin()) / Dot(normal_, r.Direction());

    if(hit_time > context.t_max_ || hit_time < context.t_min_)
        return false;

    context.t_max_ = hit_time;
    context.point_ = r.At(hit_time);
    context.normal_ = normal_;

    return true;
}

std::string Plane::toString() const {
    std::stringstream ss;

    ss << "Plane: [\n";

    ss << point_.toString() << "\n";
    ss << normal_.toString() << "\n";

    ss << "]";

    return ss.str();
}