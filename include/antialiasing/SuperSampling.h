//
// Created by Dustin on 11/1/26.
//

#ifndef WHITTED_SUPERSAMPLING_H
#define WHITTED_SUPERSAMPLING_H

#include "AntiAliasingInterface.h"

class SuperSampling : public AntiAliasingInterface {
public:
    SuperSampling(std::unique_ptr<SamplerInterface>& sampler);
    virtual ~SuperSampling() = default;

    Color SamplePixel(const Scene& scene, const ImagePlane& p, std::size_t x, std::size_t y) override;
private:
};

#endif //WHITTED_SUPERSAMPLING_H
