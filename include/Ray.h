//
// Created by Advil on 11/2/2024.
//

#ifndef WHITTED_RAY_H
#define WHITTED_RAY_H

#include "Vector.h"
#include "Point.h"

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
    Ray(const Point3d& origin, const Vec3d& direction, RayType type)
        : origin_(origin), direction_(direction.UnitVector()), type_(type) { }

    Point3d At(double t) const;
    Point3d Origin() const;
    Vec3d Direction() const;

    std::string toString() const;


private:
    Point3d origin_;
    Vec3d direction_;
    RayType type_;
};



#endif //WHITTED_RAY_H
