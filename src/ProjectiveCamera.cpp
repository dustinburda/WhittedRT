//
// Created by Advil on 11/3/2024.
//

#include "../include/ProjectiveCamera.h"

std::vector<Ray> ProjectiveCamera::GetRayAt(int x, int y) const
{
    double height = (1.0 / v_y_[1]) * (-2.0 / 1.0);
    double width = height * aspect_ratio_;
    Point3d upper_left_corner { -0.5 * (width * v_x_[0] + height * v_y_[0]), -0.5 * (width * v_x_[1] + height * v_y_[1]), 0.0};


    std::vector<Point3d> pixel_samples = s_->Sample(upper_left_corner + x * v_x_ + y * v_y_, v_x_, v_y_);
    Point3d origin {0.0, 0.0, -focal_distance_};
    std::vector<Ray> rays;
    rays.reserve(pixel_samples.size());
    for (auto pixel_sample : pixel_samples)
        rays.emplace_back(origin, pixel_sample - origin, RayType::PrimaryRay);

    return rays;

//    Point3d pixel_coord = upper_left_corner + 0.5 * (v_x_ + v_y_) + x * v_x_ + y * v_y_;
//
//    return {{origin, pixel_coord - origin, RayType::PrimaryRay}};

}