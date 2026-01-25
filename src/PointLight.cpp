//
// Created by Dustin on 9/29/25.
//

#include "../include/PointLight.h"


PointLight::PointLight(Point3d position, double intensity, Color light_color)
    : position_{position}, Light{intensity, light_color} {}

Vec3d PointLight::GetDirection(ShadeContext& ctx) const {
    return (position_ - ctx.point_).UnitVector();
}