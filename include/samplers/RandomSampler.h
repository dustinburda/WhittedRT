#include "SamplerInterface.h"
#include "../util/Util.h"


class RandomSampler : public SamplerInterface
{
public:
    RandomSampler(int num_samples) : SamplerInterface{num_samples} {}
    ~RandomSampler() override = default;
    std::vector<Point2D> Samples() override;
};