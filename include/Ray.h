//
// Created by Advil on 11/2/2024.
//

#ifndef WHITTED_RAY_H
#define WHITTED_RAY_H

#include "../include/Vector.h"
#include "../include/Point.h"

enum class RayType {
    PrimaryRay,
    SecondaryRay,
    ShadowRay,
    LightRay
};

// Ray Direction is normalized
class Ray {
public:
    Ray() = default;
    Ray(Point3d origin, Vec3d direction, RayType type)
        : origin_(origin), direction_(direction.UnitVector()), type_(type) { }

    Point3d At(double t) { return origin_ + t * direction_; }
    Point3d Origin() const { return origin_; }
    Vec3d Direction() const { return direction_; }


private:
    Point3d origin_;
    Vec3d direction_;
    RayType type_;
};

static std::ostream& operator<<(std::ostream& os, const Ray &r)
{
    os << r.Origin() << r.Direction();
    return os;
}


#endif //WHITTED_RAY_H
