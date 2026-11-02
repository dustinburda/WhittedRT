//
// Created by Dustin on 9/29/25.
//

#ifndef WHITTED_AMBIENTLIGHT_H
#define WHITTED_AMBIENTLIGHT_H

#include "LightInterface.h"

class AmbientLight : public LightInterface {
public:
    AmbientLight (double intensity, Color light_color)
        : LightInterface(intensity, light_color) {}

    virtual Vec3D GetDirection([[ maybe_unused ]] ShadeContext& ctx) const {
        return Vec3D {0.0, 0.0, 0.0};
    }
};


#endif //WHITTED_AMBIENTLIGHT_H
