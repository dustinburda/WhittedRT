#include "../include/RandomSampler.h"

std::vector<Point3D> RandomSampler::Sample(Point3D origin, Vec3D Vx, Vec3D Vy)
{
    std::vector<Point3D> samples;

    for (int i = 0; i < num_samples_; i++) {
        Point3D pixel_center = origin + 0.5 * Vx + 0.5 * Vy;

        Vec3D random_offset_x =  RandomDouble(-0.5, 0.5) * Vx;
        Vec3D random_offset_y = RandomDouble(-0.5, 0.5) * Vy;

        auto sample = pixel_center + random_offset_x + random_offset_y;
        samples.push_back(sample);
    }

    return samples;
}