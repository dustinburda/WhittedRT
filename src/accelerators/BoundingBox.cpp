//
// Created by Dustin on 12/22/24.
//


#include "../../include/accelerators/BoundingBox.h"
#include "../../include/util/Interval.h"

BoundingBox::BoundingBox(Point3D p1, Point3D p2) {
    for(int i = 0; i < 3; i++) {
        min_[i] = std::min(p1[i], p2[i]);
        max_[i] = std::max(p1[i], p2[i]);
    }
}

bool BoundingBox::Hit(const Ray& r, [[ maybe_unused ]] ShadeContext& context) const {
    Point3D orig = r.Origin();
    Vec3D dir = r.Direction();

    Interval x_interval {(min_[0] - orig[0])/dir[0], (max_[0] - orig[0])/dir[0] };
    Interval y_interval {(min_[1] - orig[1])/dir[1], (max_[1] - orig[1])/dir[1] };
    Interval z_interval {(min_[2] - orig[2])/dir[2], (max_[2] - orig[2])/dir[2] };
    Interval allowable {context.t_min_, context.t_max_};

    return Interval::Intersects({x_interval, y_interval, z_interval, allowable});
}

double BoundingBox::Width() const {
    return std::abs(max_[0] - min_[0]);
}

double BoundingBox::Height() const {
    return std::abs(max_[1] - min_[1]);
}

double BoundingBox::Length() const {
    return std::abs(max_[2] - min_[2]);
}

Point3D BoundingBox::Centroid() const {
    auto centroid_vector = 0.5 * (min_.ToVector() + max_.ToVector() );

    return {centroid_vector[0], centroid_vector[1], centroid_vector[2]};
}

double BoundingBox::SurfaceArea() const {
    double f1Area = Height() * Width();
    double f2Area = Width() * Length();
    double f3Area = Height() * Length();

    return 2 * (f1Area + f2Area + f3Area);
}

BoundingBox Union(const BoundingBox& b1, const BoundingBox& b2) {
    Point3D min1 = b1.Min();
    Point3D max1 = b1.Max();

    Point3D min2 = b2.Min();
    Point3D max2 = b2.Max();

    Point3D new_min;
    Point3D new_max;

    for(int i = 0; i < 3; i++) {
        new_min[i] = std::min(min1[i], min2[i]);
        new_max[i] = std::max(max1[i], max2[i]);
    }

    return {new_min, new_max};
}
