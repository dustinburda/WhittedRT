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

    Plane(const Point<double, 3>& point, const Normal<double, 3>& normal, std::shared_ptr<Material> mat)
        : point_{point}, normal_{normal}, mat_{std::move(mat)} {}

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;

private:
    Point<double, 3> point_;
    Normal<double, 3> normal_;
    std::shared_ptr<Material> mat_;
};


#endif //WHITTED_PLANE_H
