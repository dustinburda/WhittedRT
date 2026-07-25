//
// Created by Dustin on 9/29/25.
//

#ifndef WHITTED_AMBIENTLIGHT_H
#define WHITTED_AMBIENTLIGHT_H

#include "Light.h"

class AmbientLight : public Light {
public:
    AmbientLight (double intensity, Color light_color)
        : Light(intensity, light_color) {}

    virtual Vec3D GetDirection([[ maybe_unused ]] ShadeContext& ctx) const {
        return Vec3D {0.0, 0.0, 0.0};
    }
};


#endif //WHITTED_AMBIENTLIGHT_H
