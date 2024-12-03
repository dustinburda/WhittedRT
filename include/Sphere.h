//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SPHERE_H
#define WHITTED_SPHERE_H

#include <utility>
#include <memory>

#include "Material.h"
#include "Point.h"
#include "Shape.h"
#include "ShadeContext.h"
#include "Vector.h"


class Sphere : public Shape {
public:
    Sphere() : center_{0,0,0}, radius_{1.0} {}
    Sphere(const Point<double, 3>& center, double radius, std::shared_ptr<Material> mat = nullptr)
        : center_{center}, radius_{radius} {}
    ~Sphere() override = default;

    bool Hit(const Ray& r, ShadeContext& context) const override;
    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;

private:
    Point<double, 3> center_;
    double radius_;
};


#endif //WHITTED_SPHERE_H
