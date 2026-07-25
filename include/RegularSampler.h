#include "../include/Sampler.h"

class RegularSampler : public Sampler
{
public:
    RegularSampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point3D> Sample(Point3D origin, Vec3D Vx, Vec3D Vy) override;
};
