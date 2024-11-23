//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_PLANE_H
#define WHITTED_PLANE_H

#include <cmath>
#include <memory>

#include "Globals.h"
#include "Normal.h"
#include "Point.h"
#include "Shape.h"

class Plane : public Shape {
public:
    Plane() : point_{1.0, 0.0, 0.0}, normal_{1.0, 1.0, 1.0} {}

    Plane(Point<double, 3>& point, Normal<double, 3>& normal, std::shared_ptr<Material> mat)
        : point_{point}, normal_{normal}, mat_{std::move(mat)} {}

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override
    {
        return normal_;
    }

    bool Hit(const Ray& r, ShadeContext& context) const override
    {
        // Ray parallel to Plane
        if (std::abs(Dot(r.Direction(), normal_)) <= epsilon)
            return false;

        double hit_time = Dot(normal_, point_- r.Origin()) / Dot(normal_, r.Direction());\

        if(hit_time > context.t_max_ || hit_time < context.t_min_)
            return false;

        context.t_max_ = hit_time;
        context.mat_ = mat_;
        context.point_ = r.At(hit_time);
        context.normal_ = normal_;

        return true;
    }

private:
    Point<double, 3> point_;
    Normal<double, 3> normal_;
    std::shared_ptr<Material> mat_;
};


#endif //WHITTED_PLANE_H
