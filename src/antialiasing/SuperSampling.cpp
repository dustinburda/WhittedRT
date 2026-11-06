//
// Created by Dustin on 11/2/26.
//

#include "../../include/antialiasing/SuperSampling.h"
#include "../../include/util/Trace.h"

Color SuperSampling::SamplePixel(const Scene& scene, const ImagePlane& p, std::size_t x, std::size_t y) {
    Color pixel_color;

    auto samples = scene.sampler_->Samples();
    for (auto& sample : samples) {
        // TODO: sampler samples from [0,1]^2 but GetRayAt samples from center
        auto ray = scene.camera_->GetRayAt(static_cast<double>(x) + sample[0], static_cast<double>(y) + sample[1], p);
        ShadeContext context;
        pixel_color += Trace(scene, ray, context) / static_cast<float> (samples.size());
    }

    return pixel_color;
}

