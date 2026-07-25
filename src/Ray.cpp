//
// Created by Advil on 11/2/2024.
//

#include "../include/Ray.h"

#include <string>
#include <sstream>

Point3D Ray::At(double t) const { return origin_ + t * direction_; }
Point3D Ray::Origin() const { return origin_; }
Vec3D Ray::Direction() const { return direction_; }

std::string RayTypeToString(RayType type) {
#define X(name) \
    if (type == RayType::name) \
    return #name;
        RAY_TYPES
#undef X

    return "Unknown";
}

std::string Ray::ToString() const {
    std::stringstream ss;

    ss << "Ray: \n[\n";

    ss << "\t" << origin_.toString() << "\n";
    ss << "\t" << direction_.toString() << "\n";
    ss << "\t" << RayTypeToString(type_) << "\n";
    ss << "]";

    return ss.str();
}