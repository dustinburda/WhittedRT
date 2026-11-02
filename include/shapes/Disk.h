//
// Created by Dustin on 9/13/26.
//

#ifndef WHITTED_DISK_H
#define WHITTED_DISK_H

#include "ShapeInterface.h"

class Disk : public ShapeInterface {
public:
    Disk();
    Disk(Normal<double, 3> normal, Point3D center);

    virtual ~Disk() override;

    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;
    bool Hit(const Ray& r, ShadeContext& context) const override;
    BoundingBox BBox() const override;
    std::vector<std::shared_ptr<ShapeInterface>> Decompose() const override;;

private:
    // TODO: remove center
    Normal<double, 3> normal_;
    Point3D center_;
};


#endif //WHITTED_DISK_H
