#include "../include/HammersleySampler.h"


double phi(int i) {

    double result = 0;

    double denominator = 2.0f;
    while (i > 0) {
        result += (i % 2) / denominator;

        denominator *= 2.0f;
        i >>= 1;
    }

    return result;
}

std::vector<Point3d> HammersleySampler::Sample(Point3d origin, Vec3d Vx, Vec3d Vy) {
    std::vector<Point3d> samples;

    for (int i = 0; i < num_samples_; i++) {
        double x_coordinate = i / static_cast<double>(num_samples_);
        double y_coordinate = phi(i);

        samples.push_back(origin +  x_coordinate * Vx + y_coordinate * Vy);
    }

    return samples;
}