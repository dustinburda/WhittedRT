#include "SamplerInterface.h"

class HammersleySampler : public SamplerInterface
{
public:
    HammersleySampler(int num_samples) : SamplerInterface{num_samples} {}
    ~HammersleySampler() override = default;
    std::vector<Point2D> Samples() override;
};

double phi(int i);