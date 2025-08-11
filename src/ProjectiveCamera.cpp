//
// Created by Advil on 11/3/2024.
//

#include "../include/ProjectiveCamera.h"
#include "../include/Util.h"

std::vector<Ray> ProjectiveCamera::GetRayAt(int x, int y) const
{
    double height = (1.0 / v_y_[1]) * (-2.0 / 1.0);
    double width = height * aspect_ratio_;
    Point3d canvas_upper_left_corner { -0.5 * (width * v_x_[0] + height * v_y_[0]), -0.5 * (width * v_x_[1] + height * v_y_[1]), 0.0};
    Point3d pixel_upper_left_corner = canvas_upper_left_corner + x * v_x_ + y * v_y_;


    std::vector<Point3d> pixel_samples = s_->Sample(pixel_upper_left_corner, v_x_, v_y_);
    Point3d origin {0.0, 0.0, -focal_distance_};
    std::vector<Ray> rays;
    rays.reserve(pixel_samples.size());
    for (auto pixel_sample : pixel_samples)
        rays.emplace_back(origin, pixel_sample - origin, RayType::PrimaryRay);

    return rays;
}