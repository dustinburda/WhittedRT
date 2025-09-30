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
    PointLight(Point3d position, double intensity, Color light_color) : position_{position}, intensity_{intensity}, light_color_{light_color} {}
private:
    Point3d position_;
    double intensity_;
    Color light_color_;
};


#endif //WHITTED_POINTLIGHT_H
