//
// Created by Advil on 11/23/2024.
//

#include "../include/Triangle.h"


Normal<double, 3> Triangle::NormalAt(const Point<double, 3> &p) const
{
    auto cross_product = Cross(points_[1] - points_[0], points_[2] - points_[0]);
    auto normalized_cross_product = cross_product.UnitVector();

    return Normal<double, 3> {normalized_cross_product[0], normalized_cross_product[1], normalized_cross_product[2]};
}

bool Triangle::Hit(const Ray &r, ShadeContext &context) const
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


[[nodiscard]] bool Triangle::InTriangle(const Point<double, 3>& hit_point) const {
    auto [l1, l2, l3] = BarycentricCoordinates(hit_point);

    return (l1 >= 0 && l2 >= 0 && l3 >= 0);
}

std::array<double, 3> Triangle::BarycentricCoordinates(const Point<double, 3>& hit_point) const {
    double x1 = hit_point[0];
    double x2 = hit_point[1];

    double a1 = points_[0][0];
    double a2 = points_[0][1];

    double b1 = points_[1][0];
    double b2 = points_[1][1];

    double c1 = points_[2][0];
    double c2 = points_[2][1];

    double l3 = ((x1 - a1) * (c2 - a2) - (x2 - a2) * (c1 - a1)) / ((b1 - a1) * (c2 - a2) - (b2 - a2) * (c1 - a1));
    double l2 = ((x1 - a1) * (b2 - a2)- (x2 - a2) * (b1 - a1) ) / ((c1 - a1) * (b2 - a2) - (c2 - a2) * (b1 - a1) );

    return { 1 - l2 - l3, l2, l3};
}