#include "../include/Sampler.h"
#include "../include/Util.h"

class JitteredSampler : public Sampler
{
public:
    JitteredSampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point3D> Sample(Point3D origin, Vec3D Vx, Vec3D Vy) override;
};
