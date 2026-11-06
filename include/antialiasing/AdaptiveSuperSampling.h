//
// Created by Dustin on 11/1/26.
//

#ifndef WHITTED_ADAPTIVESUPERSAMPLING_H
#define WHITTED_ADAPTIVESUPERSAMPLING_H

#include "AntiAliasingInterface.h"

class AdaptiveSuperSampling : public AntiAliasingInterface {
public:
    AdaptiveSuperSampling(std::unique_ptr<SamplerInterface>& sampler, int depth, double threshold);
    virtual ~AdaptiveSuperSampling() = default;

    Color SamplePixel(const Scene& scene, const ImagePlane& p, std::size_t x, std::size_t y) override;

private:
    Color SamplePixelInternal(const Scene& scene, const ImagePlane& p, double x, double, double length, int depth);

private:
    int depth_guard_;
    double threshold_;
};

#endif //WHITTED_ADAPTIVESUPERSAMPLING_H
