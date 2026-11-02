#include "SamplerInterface.h"
#include "../util/Util.h"

class JitteredSampler : public SamplerInterface
{
public:
    JitteredSampler(int num_samples) : SamplerInterface{num_samples} {}
    std::vector<Point2D> Samples() override;
};
