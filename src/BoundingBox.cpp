//
// Created by Dustin on 12/22/24.
//

#include "../include/BoundingBox.h"


bool Interval::operator<(const Interval& other) const {
    if (t_min_ < other.t_min_)
        return true;
    if (t_min_ > other.t_min_)
        return false;
    return t_max_ < other.t_max_;
}

bool Interval::Intersects(std::vector<Interval> intervals) {
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

BoundingBox::BoundingBox(Point3d p1, Point3d p2) {
    for(int i = 0; i < 3; i++) {
        min_[i] = std::min(p1[i], p2[i]);
        max_[i] = std::max(p1[i], p2[i]);
    }
}

bool BoundingBox::Hit(const Ray& r, ShadeContext& context) const {
    Point3d orig = r.Origin();
    Vec3d dir = r.Direction();

    Interval x_interval {(min_[0] - orig[0])/dir[0], (max_[0] - orig[0])/dir[0] };
    Interval y_interval {(min_[1] - orig[1])/dir[1], (max_[1] - orig[1])/dir[1] };
    Interval z_interval {(min_[2] - orig[2])/dir[2], (max_[2] - orig[2])/dir[2] };

    return Interval::Intersects({x_interval, y_interval, z_interval});
}

std::string BoundingBox::toString() const {
    std::stringstream ss;

    ss << min_.toString() << "\n" << max_.toString();

    return ss.str();
}

BoundingBox Union(const BoundingBox& b1, const BoundingBox& b2) {
    Point3d min1 = b1.Min();
    Point3d max1 = b1.Max();

    Point3d min2 = b2.Min();
    Point3d max2 = b2.Max();

    Point3d new_min;
    Point3d new_max;

    for(int i = 0; i < 3; i++) {
        new_min[i] = std::min(min1[i], min2[i]);
        new_max[i] = std::max(max1[i], max2[i]);
    }

    return {new_min, new_max};
}

