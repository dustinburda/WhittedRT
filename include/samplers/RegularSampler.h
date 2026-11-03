#include "SamplerInterface.h"

class RegularSampler : public SamplerInterface
{
public:
    RegularSampler(int num_samples) : SamplerInterface{num_samples} {}
    ~RegularSampler() override = default;
    std::vector<Point2D> Samples() override;
};
