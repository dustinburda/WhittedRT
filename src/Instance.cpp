//
// Created by Dustin on 12/1/24.
//

#include "../include/Instance.h"


Normal<double, 3> Instance::NormalAt(const Point<double, 3>& p) const {
    return transform_(shape_->NormalAt(p));
};

bool Instance::Hit(const Ray& r, ShadeContext& context) const {
    Ray transformed_ray = transform_.ApplyInverse(r);

    if(!shape_->Hit(transformed_ray, context))
        return false;

    context.normal_ = NormalAt(context.point_);
    context.point_ = transform_(context.point_);
    context.mat_ = mat_;

    return true;
}
