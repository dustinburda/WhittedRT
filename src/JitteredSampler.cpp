#include "../include/JitteredSampler.h"

std::vector<Point3d> JitteredSampler::Sample(Point3d origin, Vec3d Vx, Vec3d Vy) {
    std::vector<Point3d> samples;

    int num_samples_per_dimension = (std::ceil(std::sqrt(num_samples_)) + 1);

    for(int i = 0; i < num_samples_per_dimension; i++) {
        for(int j = 0; j < num_samples_per_dimension; j++) {
            Point3d pixel_center = origin + i * (Vx / num_samples_per_dimension) + j * (Vy / num_samples_per_dimension);

            Vec3d random_offset_x = RandomDouble(-0.5, 0.5) * (Vx / num_samples_per_dimension);
            Vec3d random_offset_y = RandomDouble(-0.5, 0.5) * (Vy / num_samples_per_dimension);

            auto sample = pixel_center + random_offset_x + random_offset_y;

            samples.push_back(sample);
        }
    }


    return samples;
}