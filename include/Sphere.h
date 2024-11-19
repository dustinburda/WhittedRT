//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SPHERE_H
#define WHITTED_SPHERE_H

#include "Shape.h"
#include "Vector.h"
#include "Point.h"
#include "ShadeContext.h"

class Sphere : public Shape {
public:
    Sphere() : center_{0,0,0}, radius_{1.0} {}
    Sphere(Point<double, 3>& center, double radius)
        : center_{center}, radius_{radius} {}

    bool Hit(const Ray& r, ShadeContext& context) const override { return true; }

    Normal<double, 3> NormalAt(Point<double, 3>& p) const override { return Normal<double, 3> {0,0,0}; }

private:
    Point<double, 3> center_;
    double radius_;
};


#endif //WHITTED_SPHERE_H
