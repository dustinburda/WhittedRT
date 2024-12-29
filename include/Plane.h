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
#include "ShapeInterface.h"

class Plane : public ShapeInterface {
public:
    Plane() : point_{1.0, 0.0, 0.0}, normal_{1.0, 1.0, 1.0} {}
    Plane(const Point<double, 3>& point, const Normal<double, 3>& normal)
        : point_{point}, normal_{normal} {}
    ~Plane() override = default;

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;

    std::string toString() const;

private:
    Point<double, 3> point_;
    Normal<double, 3> normal_;
};


#endif //WHITTED_PLANE_H
