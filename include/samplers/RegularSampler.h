#include "SamplerInterface.h"

class RegularSampler : public SamplerInterface
{
public:
    RegularSampler(int num_samples) : SamplerInterface{num_samples} {}
    std::vector<Point2D> Samples() override;
};
