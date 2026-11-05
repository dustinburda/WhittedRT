//
// Created by Dustin on 1/26/26.
//

#ifndef WHITTED_BOX_H
#define WHITTED_BOX_H

#include "ShapeInterface.h"

class Box : public ShapeInterface {
    Box();
    virtual ~Box() = default;

    std::optional<Normal<double, 3>> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;

    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;

};

#endif //WHITTED_BOX_H
