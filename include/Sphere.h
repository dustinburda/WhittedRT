//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SPHERE_H
#define WHITTED_SPHERE_H

#include "BoundingBox.h"
#include "Material.h"
#include "Point.h"
#include "ShapeInterface.h"
#include "ShadeContext.h"
#include "Vector.h"

#include <utility>
#include <memory>

class Sphere : public ShapeInterface {
public:
    Sphere();
    Sphere(const Point<double, 3>& center, double radius);
    ~Sphere() override = default;

    bool Hit(const Ray& r, ShadeContext& context) const override;
    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    BoundingBox BBox() const override;
    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;

    std::string toString() const;
private:
    Point<double, 3> center_;
    double radius_;
};


#endif //WHITTED_SPHERE_H
