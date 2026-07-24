//
// Created by Dustin on 9/29/25.
//

#ifndef WHITTED_LIGHT_H
#define WHITTED_LIGHT_H

#include "Color.h"
#include "Vector.h"

struct ShadeContext;

class Light {
public:
    Light();
    Light(double intensity, Color light_color);
    virtual ~Light() = default;

    // TODO: Change interface to accomodate AmbientLight
    virtual Vec3d GetDirection(ShadeContext& ctx) const = 0;

    double GetIntensity() const;
    Color GetColor() const;
private:
    double intensity_;

    // Should an ambient light have a color?
    Color light_color_;
};

#endif //WHITTED_LIGHT_H
