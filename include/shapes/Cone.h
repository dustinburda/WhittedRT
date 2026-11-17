//
// Created by Dustin on 8/13/25.
//

#ifndef WHITTED_CONE_H
#define WHITTED_CONE_H

#include "Disk.h"
#include "ShapeInterface.h"


class Cone : public ShapeInterface {
public:
    Cone();
    virtual ~Cone() = default;

    std::optional<Normal<double, 3>> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;
};


#endif //WHITTED_CONE_H
