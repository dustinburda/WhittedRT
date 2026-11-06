//
// Created by Dustin on 11/5/26.
//

#include "../../include/util/Trace.h"

Color Trace(const Scene& scene, Ray& r, ShadeContext& context) {
    if(scene.Hit(r, context))
        return context.mat_->Shade(context, scene.lights_);

    return {0.0, 0.0, 0.0};
}