//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_TRIANGLE_H
#define WHITTED_TRIANGLE_H


#include <array>
#include <memory>

#include "Globals.h"
#include "Material.h"
#include "Point.h"
#include "Shape.h"


class Triangle : public Shape {
public:
    Triangle() = default;
    Triangle(Point3d a, Point3d b, Point3d c, std::shared_ptr<Material> mat = nullptr)
        : points_{a,b,c}, mat_{std::move(mat)} {}
    ~Triangle() override = default;

    Normal<double, 3> NormalAt(const Point<double, 3> &p) const override;
    bool Hit(const Ray &r, ShadeContext &context) const override;

    std::array<Point3d, 3> Points() const { return points_; };
    std::shared_ptr<Material> GetMaterial() const { return mat_; };
private:

    [[nodiscard]] bool InTriangle(const Point<double, 3>& hit_point) const;
    std::array<double, 3> BarycentricCoordinates(const Point<double, 3>& hit_point) const;

    std::array<Point3d, 3> points_;
    std::shared_ptr<Material> mat_;
};


#endif //WHITTED_TRIANGLE_H
