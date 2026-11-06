//
// Created by Dustin on 11/2/26.
//

#include "../../include/antialiasing/AdaptiveSuperSampling.h"
#include "../../include/util/Trace.h"

#include <ranges>

Color AdaptiveSuperSampling::SamplePixel(const Scene& scene, const ImagePlane& p, std::size_t x, std::size_t y)  {
    return SamplePixelInternal(scene, p, static_cast<double>(x), static_cast<double>(y), 1.0, 0);
}

Color AdaptiveSuperSampling::SamplePixelInternal(const Scene& scene, const ImagePlane& p, double x, double y, double length, int depth) {
    auto offsets = sampler_->Samples();

    std::array<Point2D, 4> corners = {
        Point2D {x, y },
        Point2D {x + 0.5 * length, y },
        Point2D {x, y + 0.5 * length },
        Point2D {x + 0.5 * length, y + 0.5 * length },
    };

    std::array<Point2D, 4> samples = corners;
    for (auto&& [sample, offset ] : std::views::zip(samples, offsets) ) {
        sample[0] += 0.5 * length * offset[0];
        sample[1] += 0.5 * length * offset[1];
    }

    std::array<Color, 4> colors;
    for (auto&& [sample, color] : std::views::zip(samples, colors) ) {
        auto ray = scene.camera_->GetRayAt(sample[0], sample[1], p);
        ShadeContext context;
        color = Trace(scene, ray, context);
    }

    auto average_color = std::accumulate(colors.begin(), colors.end(), Color{0,0,0}) / 4.0;

    if (depth >= depth_guard_)
        return average_color;

    for (auto&& [i, color] : std::views::enumerate(colors)) {
        auto diff_r = std::abs(color.R() - average_color.R());
        auto diff_g = std::abs(color.G() - average_color.G());
        auto diff_b = std::abs(color.B() - average_color.B());

        if (diff_r > threshold_ || diff_g > threshold_ || diff_b > threshold_) {
            auto& corner = corners[i];

            color = SamplePixelInternal(scene, p, corner[0], corner[1], 0.5 * length, depth + 1);
        }
    }

    return std::accumulate(colors.begin(), colors.end(), Color{0,0,0}) / 4.0;
}