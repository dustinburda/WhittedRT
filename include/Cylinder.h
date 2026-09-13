//
// Created by Dustin on 8/13/25.
//

#ifndef WHITTED_CYLINDER_H
#define WHITTED_CYLINDER_H

#include "Disk.h"
#include "ShapeInterface.h"


class Cylinder : public ShapeInterface {
public:
    Cylinder() = default;
    Cylinder(double radius, double height);

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const  override;
    bool Hit(const Ray& r, ShadeContext& context) const  override;
    BoundingBox BBox() const  override;


private:
    Disk cap1_;
    Disk cap2_;
};


#endif //WHITTED_CYLINDER_H
