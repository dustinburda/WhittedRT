#include "../Sampler.h"
#include "../Util.h"


class RandomSampler : public Sampler
{
public:
    RandomSampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point2D> Samples() override;
};