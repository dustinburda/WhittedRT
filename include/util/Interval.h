//
// Created by Dustin on 11/4/26.
//

#ifndef WHITTED_INTERVAL_H
#define WHITTED_INTERVAL_H

#include <vector>

struct Interval {
    Interval() = default;
    explicit Interval(double t_min, double t_max) : t_min_ {std::min(t_min, t_max)}, t_max_ {std::max(t_min, t_max)} {}

    bool operator<(const Interval& other) const;
    static bool Intersects(std::vector<Interval> intervals);

    double t_min_;
    double t_max_;
};

#endif //WHITTED_INTERVAL_H
