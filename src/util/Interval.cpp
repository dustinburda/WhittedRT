//
// Created by Dustin on 11/4/26.
//

#include "../../include/util/Interval.h"

#include <algorithm>

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
    for(std::size_t i = 1; i < intervals.size(); i++) {
        const Interval& curr_interval = intervals[i];
        if(curr_interval.t_min_ > intersection.t_max_)
            return false;

        intersection.t_min_ = std::max(intersection.t_min_, curr_interval.t_min_);
        intersection.t_max_ = std::min(intersection.t_max_, curr_interval.t_max_);

    }

    return true;
}