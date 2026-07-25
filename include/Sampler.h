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
  virtual ~Sampler() = default;
  virtual std::vector<Point3D> Sample(Point3D origin, Vec3D Vx, Vec3D Vy) = 0;

protected:
  int num_samples_;
};

#endif // WHITTED_SAMPLER_H
