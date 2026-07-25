//
// Created by Advil on 11/2/2024.
//

#ifndef WHITTED_RAY_H
#define WHITTED_RAY_H

#include "Vector.h"
#include "Point.h"

#define RAY_TYPES \
    X(PrimaryRay) \
    X(SecondaryRay) \
    X(ShadowRay) \
    X(LightRay)

enum class RayType {
#define X(name) name,
    RAY_TYPES
#undef X
};

std::string RayTypeToString(RayType type);

// Ray Direction is normalized
class Ray {
public:
    Ray() = default;
    Ray(const Point3D& origin, const Vec3D& direction, RayType type)
        : origin_(origin), direction_(direction.UnitVector()), type_(type) { }

    Point3D At(double t) const;
    Point3D Origin() const;
    Vec3D Direction() const;

    std::string ToString() const;


private:
    Point3D origin_;
    Vec3D direction_;
    RayType type_;
};



#endif //WHITTED_RAY_H
