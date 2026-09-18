//
// Created by Dustin on 1/26/26.
//

#ifndef WHITTED_BOX_H
#define WHITTED_BOX_H

#include "ShapeInterface.h"

class Box : public ShapeInterface {
    Box();
    virtual ~Box() = default;

    virtual Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    virtual bool Hit(const Ray& r, ShadeContext& context) const override;
    virtual BoundingBox BBox() const override;
};

#endif //WHITTED_BOX_H
