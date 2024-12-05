//
// Created by Advil on 11/2/2024.
//

#include "../include/Ray.h"

#include <string>
#include <sstream>

Point3d Ray::At(double t) const { return origin_ + t * direction_; }
Point3d Ray::Origin() const { return origin_; }
Vec3d Ray::Direction() const { return direction_; }

std::string Ray::toString() const {
    std::stringstream ss;

    ss << "Ray: [\n";

    ss << origin_.toString() << "\n";
    ss << direction_.toString() << "\n";

    ss << "]";

    return ss.str();
}