//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SHAPE_H
#define WHITTED_SHAPE_H

#include "BoundingBox.h"
#include "Ray.h"
#include "ShadeContext.h"

enum class ShapeType {
    Sphere,
    Mesh,
    Triangle,
    Plane,
    Cylinder,
    Disk,
    Box
};

class ShapeInterface {
public:
    ShapeInterface(ShapeType type);
    virtual ~ShapeInterface() = default;
    virtual Normal<double, 3> NormalAt(const Point<double, 3>& p) const = 0;
    virtual bool Hit(const Ray& r, ShadeContext& context) const = 0;
    virtual BoundingBox BBox() const = 0;
    virtual std::vector<std::shared_ptr<ShapeInterface>> Decompose() const = 0;

    ShapeType Type() const;
private:
    ShapeType type_;
};

#endif //WHITTED_SHAPE_H