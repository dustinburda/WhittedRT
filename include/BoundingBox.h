//
// Created by Dustin on 12/22/24.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <algorithm>

#include "Point.h"
#include "Ray.h"
#include "ShadeContext.h"
#include "ShapeInterface.h"

struct Interval {
    Interval(double t_min, double t_max) : t_min_ {t_min_}, t_max_ {t_max} {}

    static bool Intersects(const std::vector<Interval>& intervals) {
        if (intervals.size() == 0)
            return true;

        std::sort(intervals.begin(), intervals.end());

        Interval intersection = intervals[0];
        for(int i = 1; i < intervals.size(); i++) {
            const Interval& curr_interval = intervals[i];
            if(curr_interval.t_min_ > intersection.t_max_)
                return false;

            intersection.t_min_ = std::max(intersection.t_min_, curr_interval.t_min_);
            intersection.t_max_ = std::min(intersection.t_max_, curr_interval.t_max_);

        }

        return true;
    }

    double t_min_;
    double t_max_;
};

// Not templated for now
class BoundingBox : public ShapeInterface {
public:
    BoundingBox() : min_{0.0 ,0.0 ,0.0}, max_{1.0, 1.0, 1.0} {}
    BoundingBox(Point3d p1, Point3d p2);

    bool Hit(const Ray& r, ShadeContext& context) const override;
    Normal<double, 3> NormalAt(const Point<double, 3>& p) const override;

    Point3d Min() const { return min_; }
    Point3d Max() const { return max_; }


private:
    Point3d min_;
    Point3d max_;
};

BoundingBox Union(BoundingBox& b1, BoundingBox& b2);



#endif //BOUNDINGBOX_H
