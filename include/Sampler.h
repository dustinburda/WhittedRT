//
// Created by Dustin on 4/24/25.
//

#ifndef WHITTED_SAMPLER_H
#define WHITTED_SAMPLER_H

#include "Point.h"
#include "Vector.h"

#include <vector>


// Interface to sample a square
class Sampler {
public:
    Sampler(int num_samples) : num_samples_{num_samples} {}
    virtual std::vector<Point3d> Sample(Point3d origin, Vec3d Vx, Vec3d Vy) = 0;
protected:
    int num_samples_;
};

#endif //WHITTED_SAMPLER_H
