#include "../include/RandomSampler.h"

std::vector<Point3d> RandomSampler::Sample(Point3d origin, Vec3d Vx, Vec3d Vy)
{
    std::vector<Point3d> samples;

    for (int i = 0; i < num_samples_; i++) {
        Point3d pixel_center = origin + 0.5 * Vx + 0.5 * Vy;

        Vec3d random_offset_x =  RandomDouble(-0.5, 0.5) * Vx;
        Vec3d random_offset_y = RandomDouble(-0.5, 0.5) * Vy;

        auto sample = pixel_center + random_offset_x + random_offset_y;
        samples.push_back(sample);
    }

    return samples;
}