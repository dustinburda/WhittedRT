//
// Created by Dustin on 9/29/25.
//

#ifndef WHITTED_POINTLIGHT_H
#define WHITTED_POINTLIGHT_H


#include "Color.h"
#include "Light.h"
#include "Point.h"


class PointLight : public Light {
public:
    PointLight(Point3D position, double intensity, Color light_color);
    Vec3D GetDirection(ShadeContext& ctx) const override;

private:
    Point3D position_;
};


#endif //WHITTED_POINTLIGHT_H
