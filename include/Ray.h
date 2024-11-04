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

class Ray {
public:
    Ray() = default;
    Ray(Point<double, 3> origin, Vector<double, 3> direction, RayType type)
        : origin_(origin), direction_(direction), type_(type) { }

    Point<double, 3> At(double t) { return origin_ + t * direction_; }
    Point<double, 3> Origin() const { return origin_; }
    Vector<double, 3> Direction() const { return direction_; }


private:
    Point<double, 3> origin_;
    Vector<double, 3> direction_;
    RayType type_;
};


#endif //WHITTED_RAY_H
