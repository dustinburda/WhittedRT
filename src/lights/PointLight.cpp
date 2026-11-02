//
// Created by Dustin on 9/29/25.
//

#include "../../include/lights/PointLight.h"
#include "../../include/renderer/ShadeContext.h"


PointLight::PointLight(Point3D position, double intensity, Color light_color)
    : LightInterface{intensity, light_color}, position_{position} {}

Vec3D PointLight::GetDirection(ShadeContext& ctx) const {
    return (position_ - ctx.point_).UnitVector();
}