//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SHAPE_H
#define WHITTED_SHAPE_H

#endif //WHITTED_SHAPE_H

#include "Ray.h"
#include "ShadeContext.h"

class Shape {
    virtual Normal<double, 3> NormalAt(const Point<double, 3>& p) const = 0;
    virtual bool Hit(const Ray& r, ShadeContext& context) const = 0;
};