#include "../../include/samplers/RandomSampler.h"

std::vector<Point2D> RandomSampler::Samples()
{
    std::vector<Point2D> samples;

    for (int i = 0; i < num_samples_; i++) {
        samples.emplace_back(Point2D {RandomDouble(-1.0, 1.0), RandomDouble(-1.0, 1.0)});
    }

    return samples;
}