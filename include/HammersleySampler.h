#include "../include/Sampler.h"

class HammersleySampler : public Sampler
{
public:
    HammersleySampler(int num_samples) : Sampler{num_samples} {}
    std::vector<Point3D> Sample(Point3D origin, Vec3D Vx, Vec3D Vy) override;
};

double phi(int i);