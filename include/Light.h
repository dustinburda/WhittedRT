//
// Created by Dustin on 9/29/25.
//

#ifndef WHITTED_LIGHT_H
#define WHITTED_LIGHT_H

#include "ShadeContext.h"

class Light {
public:
    Light();
    Light(double intensity, Color light_color);

    virtual Vec3d GetDirection(ShadeContext& ctx) const = 0;

    double GetIntensity() const;
    Color GetColor() const;
private:
    double intensity_;
    Color light_color_;
};

#endif //WHITTED_LIGHT_H
