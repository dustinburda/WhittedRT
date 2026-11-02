#include "SamplerInterface.h"

class HammersleySampler : public SamplerInterface
{
public:
    HammersleySampler(int num_samples) : SamplerInterface{num_samples} {}
    std::vector<Point2D> Samples() override;
};

double phi(int i);