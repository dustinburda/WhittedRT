//
// Created by Dustin on 4/24/25.
//

#ifndef WHITTED_SAMPLER_H
#define WHITTED_SAMPLER_H

#include "Point.h"

#include <vector>

class Sampler {
public:
    virtual std::vector<Point2d> Sample() = 0;
};


#endif //WHITTED_SAMPLER_H
