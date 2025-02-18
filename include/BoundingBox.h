//
// Created by Dustin on 12/22/24.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Point.h"
#include "Ray.h"
#include "ShadeContext.h"

#include <algorithm>

struct Interval {
    Interval() = default;
    explicit Interval(double t_min, double t_max) : t_min_ {std::min(t_min, t_max)}, t_max_ {std::max(t_min, t_max)} {}

    bool operator<(const Interval& other) const;
    static bool Intersects(std::vector<Interval> intervals);

    double t_min_;
    double t_max_;
};

// Not templated for now
class BoundingBox {
public:
    BoundingBox() : min_{0.0 ,0.0 ,0.0}, max_{1.0, 1.0, 1.0} {}
    BoundingBox(Point3d p1, Point3d p2);

    bool Hit(const Ray& r, ShadeContext& context) const;

    Point3d Min() const { return min_; }
    Point3d Max() const { return max_; }

    std::string toString() const;


private:
    Point3d min_;
    Point3d max_;
};

BoundingBox Union(const BoundingBox& b1, const BoundingBox& b2);



#endif //BOUNDINGBOX_H
