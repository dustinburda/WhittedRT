//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_SHAPE_H
#define WHITTED_SHAPE_H

#include "BoundingBox.h"
#include "Ray.h"
#include "ShadeContext.h"

#define SHAPE_TYPES \
    X(Sphere) \
    X(Mesh) \
    X(Triangle) \
    X(Plane) \
    X(Cylinder) \
    X(Disk) \
    X(Box)

enum class ShapeType {
#define X(name) name,
    SHAPE_TYPES
#undef X
};

class ShapeInterface {
public:
    ShapeInterface(ShapeType type);
    virtual ~ShapeInterface() = default;

    virtual bool Hit(const Ray& r, ShadeContext& context) const = 0;

    virtual Normal<double, 3> NormalAt(const Point<double, 3>& p) const = 0;
    virtual BoundingBox BBox() const = 0;

    virtual std::vector<std::shared_ptr<ShapeInterface>> Decompose() const = 0;

    ShapeType Type() const;
private:
    ShapeType type_;
};

#endif //WHITTED_SHAPE_H