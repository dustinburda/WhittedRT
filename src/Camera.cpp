//
// Created by Advil on 11/3/2024.
//

#include "../include/Camera.h"

Ray Camera::GetRayAt(int x, int y)
{
    double height = (1.0 / v_y_[1]) * (-2.0 / 1.0);
    double width = height * aspect_ratio_;
    Point3d upper_left_corner { -0.5 * (width * v_x_[0] + height * v_y_[0]), -0.5 * (width * v_x_[1] + height * v_y_[1]), 0.0};



    Point3d pixel_coord = upper_left_corner + 0.5 * (v_x_ + v_y_) + x * v_x_ + y * v_y_;

    // std::cout << "x: "  << x <<  " ,y: " << y << " , " << pixel_coord << "\n";

    Point3d origin {0.0, 0.0, -focal_distance_};

    return {origin, pixel_coord - origin, RayType::PrimaryRay};
}