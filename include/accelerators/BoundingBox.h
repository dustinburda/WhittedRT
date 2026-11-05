//
// Created by Dustin on 12/22/24.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../math/Point.h"
#include "../math/Ray.h"
#include "../renderer/ShadeContext.h"

// Not templated for now
class BoundingBox {
public:
    BoundingBox() : min_{0.0 ,0.0 ,0.0}, max_{0.0, 0.0, 0.0} {}
    BoundingBox(Point3D p1, Point3D p2);

    bool Hit(const Ray& r, ShadeContext& context) const;

    Point3D Min() const { return min_; }
    Point3D Max() const { return max_; }

    double Width() const;
    double Height() const;
    double Length() const;

    Point3D Centroid() const;
    double SurfaceArea() const;

private:
    Point3D min_;
    Point3D max_;
};

BoundingBox Union(const BoundingBox& b1, const BoundingBox& b2);



#endif //BOUNDINGBOX_H
