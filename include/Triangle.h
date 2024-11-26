//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_TRIANGLE_H
#define WHITTED_TRIANGLE_H


#include <array>
#include <complex>
#include <memory>

#include "Globals.h"
#include "Material.h"
#include "Point.h"
#include "Shape.h"


class Triangle : public Shape {
public:
    Triangle() = default;
    Triangle(Point3d a, Point3d b, Point3d c, std::shared_ptr<Material> mat)
        : points_{a,b,c}, mat_{std::move(mat)} {}

    Normal<double, 3> NormalAt(const Point<double, 3> &p) const override
    {
        auto cross_product = Cross(points_[1] - points_[0], points_[2] - points_[0]);
        auto normalized_cross_product = cross_product.UnitVector();

        return Normal<double, 3> {normalized_cross_product[0], normalized_cross_product[1], normalized_cross_product[2]};
    }

    bool Hit(const Ray &r, ShadeContext &context) const override
    {
        auto normal = NormalAt(points_[0]);
        if(std::abs(Dot(r.Direction(), normal)) <= epsilon)
            return false;

        double hit_time = Dot(normal, points_[0] - r.Origin()) / Dot(normal, r.Direction());
        if (hit_time > context.t_max_ || hit_time < context.t_min_)
            return false;

        auto hit_point = r.At(hit_time);

        if(!InTriangle(hit_point))
            return false;

        context.t_max_ = hit_time;
        context.mat_ = mat_;
        context.point_ = hit_point;
        context.normal_ = normal;


        return true;
    }



private:
    [[nodiscard]] bool InTriangle(const Point<double, 3>& hit_point) const {
        auto [l1, l2, l3] = BarycentricCoordinates(hit_point);

        return (l1 >= 0 && l2 >= 0 && l3 >= 0);
    }

    std::array<double, 3> BarycentricCoordinates(const Point<double, 3>& hit_point) const {
        double l2 = 0;
        double l3 = 0;

        return { 1 - l2 - l3, l2, l3};
    }

    std::array<Point3d, 3> points_;
    std::shared_ptr<Material> mat_;
};


#endif //WHITTED_TRIANGLE_H
