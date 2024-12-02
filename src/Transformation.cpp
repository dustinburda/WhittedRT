//
// Created by Dustin on 12/1/24.
//

#include "../include/Transformation.h"

Transformation Transformation::Identity() {
    Transformation t;
    t.Transform() = {1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0};
    t.InverseTransform() = Inverse(t.transform_);

    return t;
}


Transformation Transformation::Translation(double x, double y, double z) {
    Transformation t;
    t.Transform() = {1.0, 0.0, 0.0, x,
                       0.0, 1.0, 0.0, y,
                       0.0, 0.0, 1.0, z,
                       0.0, 0.0, 0.0, 1.0};
    t.InverseTransform() = Inverse(t.transform_);

    return t;
}

Transformation Transformation::RotationX(double radians) {
    Transformation t;
    double costheta = std::cos(radians);
    double sintheta = std::sin(radians);
    t.transform_ = {1.0, 0.0,      0.0,       0.0,
                      0.0, costheta, -sintheta, 0.0,
                      0.0, sintheta, costheta,  0.0,
                      0.0, 0.0,      0.0,       1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::RotationY(double radians) {
    Transformation t;
    double costheta = std::cos(radians);
    double sintheta = std::sin(radians);
    t.transform_ = {costheta,  0.0,  sintheta,  0.0,
                      0.0,       1.0,  0.0,       0.0,
                      -sintheta, 0.0,  costheta,  0.0,
                      0.0,       0.0,  0.0,       1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::RotationZ(double radians) {
    Transformation t;
    double costheta = std::cos(radians);
    double sintheta = std::sin(radians);
    t.transform_ = {costheta, -sintheta, 0.0, 0.0,
                      sintheta, costheta,  0.0, 0.0,
                      0.0,      0.0,       1.0, 0.0,
                      0.0,      0.0,       0.0, 1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::ReflectionX() {
    Transformation t;
    t.transform_ = {-1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      0.0, 0.0, 0.0, 1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::ReflectionY() {
    Transformation t;
    t.transform_ = {1.0, 0.0, 0.0, 0.0,
                      0.0, -1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      0.0, 0.0, 0.0, 1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::ReflectionZ() {
    Transformation t;
    t.transform_ = {1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, -1.0, 0.0,
                      0.0, 0.0, 0.0, 1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}

Transformation Transformation::Scale(double x, double y, double z) {
    Transformation t;
    t.transform_ = {x, 0.0, 0.0, 0.0,
                      0.0, y, 0.0, 0.0,
                      0.0, 0.0, z, 0.0,
                      0.0, 0.0, 0.0, 1.0};
    t.inverse_transform_ = Inverse(t.transform_);

    return t;
}