//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SPHERE_H
#define WHITTED_SPHERE_H

#include <utility>

#include "Material.h"
#include "Point.h"
#include "Shape.h"
#include "ShadeContext.h"
#include "Vector.h"


class Sphere : public Shape {
public:
    Sphere() : center_{0,0,0}, radius_{1.0} {}
    Sphere(const Point<double, 3>& center, double radius, std::shared_ptr<Material> mat)
        : center_{center}, radius_{radius}, mat_{std::move(mat)} {}

    bool Hit(const Ray& r, ShadeContext& context) const override {
        double a = Dot(r.Direction(), r.Direction());
        double b = 2 * Dot(r.Direction(), r.Origin() - center_);
        double c = Dot(r.Origin() - center_, r.Origin() - center_) - radius_ * radius_;

        double discriminant = b * b - 4 * a * c;

        double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

        double hit_time = t1;
        if (t1 > context.t_max_ || t1 < context.t_min_)
        {
            hit_time = t2;
            if (t2 > context.t_max_ || t2 < context.t_min_)
                return false;
        }


        context.t_max_ = hit_time;
        context.mat_ = mat_;
        context.point_ = r.At(hit_time);
        context.normal_ = NormalAt(r.At(hit_time));

        return discriminant > 0;
    }

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override {
        Vector<double, 3> diff = p - center_;
        return Normal<double, 3> {diff[0], diff[1], diff[2]};
    }

private:
    Point<double, 3> center_;
    double radius_;
    std::shared_ptr<Material> mat_;
};


#endif //WHITTED_SPHERE_H
