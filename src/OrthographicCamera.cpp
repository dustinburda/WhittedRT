//
// Created by Dustin on 12/6/24.
//

#include "../include/OrthographicCamera.h"

std::vector<Ray> OrthographicCamera::GetRayAt(int x, int y) const {
    double height = (1.0 / v_y_[1]) * (-2.0 / 1.0);
    double width = height * aspect_ratio_;
    Point3d upper_left_corner { -0.5 * (width * v_x_[0] + height * v_y_[0]), -0.5 * (width * v_x_[1] + height * v_y_[1]), 0.0};

    std::vector<Point3d> pixel_samples = s_->Sample(upper_left_corner, v_x_, v_y_);

    std::vector<Ray> rays;
    rays.reserve(pixel_samples.size());
    for (auto pixel_sample : pixel_samples)
        rays.emplace_back(pixel_sample, Vec3d{0.0, 0.0, 1.0}, RayType::PrimaryRay);

    return rays;
}