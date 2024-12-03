//
// Created by Dustin on 12/1/24.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include "Shape.h"
#include "Transformation.h"

#include <memory>

class Instance : public Shape {
public:
    Instance() = delete;
    Instance(std::shared_ptr<Shape> shape) : transform_{Transformation::Identity()}, shape_{std::move(shape)} {}
    Instance(Transformation t, std::shared_ptr<Shape> shape)
        :transform_{t}, shape_{std::move(shape)} {}

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override {
        return transform_(shape_->NormalAt(p));
    };

    bool Hit(const Ray& r, ShadeContext& context) const override{
        Ray transformed_ray = transform_.ApplyInverse(r);

        if(!shape_->Hit(transformed_ray, context))
            return false;

        context.normal_ = NormalAt(context.point_);
        context.point_ = transform_(context.point_);

        return true;
    }


private:
    Transformation transform_;
    std::shared_ptr<Shape> shape_;
};



#endif //INSTANCE_H
