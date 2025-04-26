#include "../include/Sampler.h"

class RegularSampler : public Sampler
{
public:
    RegularSampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point3d> Sample(Point3d origin, Vec3d Vx, Vec3d Vy) override;
};
