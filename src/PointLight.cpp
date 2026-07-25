//
// Created by Dustin on 9/29/25.
//

#include "../include/PointLight.h"
#include "../include/ShadeContext.h"


PointLight::PointLight(Point3D position, double intensity, Color light_color)
    : Light{intensity, light_color}, position_{position} {}

Vec3D PointLight::GetDirection(ShadeContext& ctx) const {
    return (position_ - ctx.point_).UnitVector();
}