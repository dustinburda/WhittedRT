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
    Instance(std::shared_ptr<Shape> shape, std::shared_ptr<Material> mat_ = nullptr)
        : shape_{std::move(shape)}, transform_{Transformation::Identity()}, mat_{mat_} {}
    Instance(std::shared_ptr<Shape> shape, Transformation t, std::shared_ptr<Material> mat_ = nullptr)
        : shape_{std::move(shape)}, transform_{Transformation::Identity()}, mat_{mat_} {}

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override {
        return transform_(shape_->NormalAt(p));
    };

    bool Hit(const Ray& r, ShadeContext& context) const override{
        Ray transformed_ray = transform_.ApplyInverse(r);

        if(!shape_->Hit(transformed_ray, context))
            return false;

        context.normal_ = NormalAt(context.point_);
        context.point_ = transform_(context.point_);
        context.mat_ = mat_;

        return true;
    }


private:
    Transformation transform_;
    std::shared_ptr<Shape> shape_;
    std::shared_ptr<Material> mat_;
};



#endif //INSTANCE_H
