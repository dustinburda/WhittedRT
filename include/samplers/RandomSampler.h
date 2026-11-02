#include "SamplerInterface.h"
#include "../util/Util.h"


class RandomSampler : public SamplerInterface
{
public:
    RandomSampler(int num_samples) : SamplerInterface{num_samples} {}
    std::vector<Point2D> Samples() override;
};