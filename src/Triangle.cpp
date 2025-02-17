//
// Created by Advil on 11/23/2024.
//

#include "../include/Triangle.h"

#include "../include/Globals.h"

#include <cassert>
#include <sstream>
#include <string>

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
    context.point_ = hit_point;
    context.normal_ = normal;

    return true;
}

BoundingBox Triangle::BBox() const {
    Point3d min { std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };
    Point3d max { std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min() };



    for (auto& point : points_) {
        for (int i = 0; i < 3; i++) {
            min[i] = std::min(min[i], point[i]);
            max[i] = std::max(max[i], point[i]);
        }
    }

    return BoundingBox {min, max};
}


[[nodiscard]] bool Triangle::InTriangle(const Point<double, 3>& hit_point) const {
    auto coordinates = BarycentricCoordinates(hit_point);

    double l1 = coordinates[0];
    double l2 = coordinates[1];
    double l3 = coordinates[2];

    return (l1 >= 0 && l2 >= 0 && l3 >= 0 && std::abs(l1 + l2 + l3 - 1) < epsilon);
}

std::array<double, 3> Triangle::BarycentricCoordinates(const Point<double, 3>& hit_point) const {
    std::array<double, 3> barycentric_coordinates {0.0, 0.0, 0.0};

    double area_triangle = Cross(points_[1] - points_[0], points_[2] - points_[0]).Length() / 2;

    for(int i = 0; i < 3; i++) {
        double area_sub_triangle = Cross(points_[(i + 1) % 3] - points_[i % 3], hit_point - points_[i % 3]).Length() / 2.0;
        barycentric_coordinates[(i + 2) % 3] = area_sub_triangle / area_triangle;
    }

    return barycentric_coordinates;
}

std::string Triangle::toString() const {
    std::stringstream ss;

    ss << "Triangle: [\n";

    ss << points_[0].toString();
    ss << "\n";
    ss << points_[1].toString();
    ss << "\n";
    ss << points_[2].toString();
    ss << "\n";

    ss <<"]";

    return ss.str();
}

