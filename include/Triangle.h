//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_TRIANGLE_H
#define WHITTED_TRIANGLE_H

#include "Point.h"
#include "ShapeInterface.h"

#include <array>

class Triangle : public ShapeInterface {
public:
    Triangle() = default;
    Triangle(Point3d a, Point3d b, Point3d c)
        : points_{a,b,c} {}
    ~Triangle() override = default;

    Normal<double, 3> NormalAt(const Point<double, 3> &p) const override;
    bool Hit(const Ray &r, ShadeContext &context) const override;
    BoundingBox BBox() const override;

    std::string toString() const;
private:

    [[nodiscard]] bool InTriangle(const Point<double, 3>& hit_point) const;
    std::array<double, 3> BarycentricCoordinates(const Point<double, 3>& hit_point) const;

    std::array<Point3d, 3> points_;
};


#endif //WHITTED_TRIANGLE_H
