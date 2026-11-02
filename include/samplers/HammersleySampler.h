#include "../Sampler.h"

class HammersleySampler : public Sampler
{
public:
    HammersleySampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point2D> Samples() override;
};

double phi(int i);