#include "../include/RegularSampler.h"

std::vector<Point3D> RegularSampler::Sample(Point3D origin, Vec3D Vx, Vec3D Vy) {
    std::vector<Point3D> samples;

    int num_samples_per_dimension = (std::ceil(std::sqrt(num_samples_)) + 1); // Number of dimensions

    for(int i = 0; i < num_samples_per_dimension; i++) {
        for(int j = 0; j < num_samples_per_dimension; j++) {
            auto sample = origin + i * (Vx / num_samples_per_dimension) + j * (Vy / num_samples_per_dimension);
            samples.push_back(sample);
        }
    }

    return samples;
}