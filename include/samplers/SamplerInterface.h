#ifndef WHITTED_SAMPLER_H
#define WHITTED_SAMPLER_H

#include "../math/Point.h"
#include "../math/Vector.h"

#include <vector>

// Interface to sample a square
class SamplerInterface {
public:
  SamplerInterface(int num_samples) : num_samples_{num_samples} {}
  virtual ~SamplerInterface() = default;
  virtual std::vector<Point2D> Samples() = 0;

protected:
  int num_samples_;
};

#endif // WHITTED_SAMPLER_H
