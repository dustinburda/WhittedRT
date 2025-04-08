//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_TRIANGLE_H
#define WHITTED_TRIANGLE_H

#include "Point.h"
#include "ShapeInterface.h"

#include <array>
#include <optional>

struct Vertex {
    Vertex(Point3d position) : position_{position}, texture_coordinate_{std::nullopt} {}
    Vertex(Point3d position, std::optional<Point2d> texture_coordinate) : position_{position}, texture_coordinate_{texture_coordinate} {}

    Point3d position_;
    std::optional<Point2d> texture_coordinate_;
};

class Triangle : public ShapeInterface {
public:
    Triangle() = default;
    Triangle(Vertex a, Vertex b, Vertex c)
        : vertices_{a,b,c}, is_textured_{false} {}
    ~Triangle() override = default;

    Normal<double, 3> NormalAt(const Point<double, 3> &p) const override;
    bool Hit(const Ray &r, ShadeContext &context) const override;
    BoundingBox BBox() const override;
    void SetIsTextured(bool is_textured);

    std::string toString() const;
private:

    [[nodiscard]] bool InTriangle(const Point<double, 3>& hit_point) const;
    std::array<double, 3> BarycentricCoordinates(const Point<double, 3>& hit_point) const;

    std::array<Vertex, 3> vertices_;
    bool is_textured_;
};


#endif //WHITTED_TRIANGLE_H
