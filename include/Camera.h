//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_CAMERA_H
#define WHITTED_CAMERA_H

#include <cstdint>

#include "Point.h"
#include "Vector.h"
#include "Ray.h"


class Camera {
public:
    Camera() = delete;
    Camera(int width, int height, double focal_distance)
        : focal_distance_ {static_cast<double>(focal_distance)}, aspect_ratio_{static_cast<double>(width) / static_cast<double>(height) }, v_x_ {2.0 * aspect_ratio_ / width, 0.0, 0.0}, v_y_{0.0, 2.0 * (-1.0) / height, 0.0} {}
    Ray GetRayAt(int x, int y);

private:
    double focal_distance_;
    double aspect_ratio_;
    // Note v_x_, v_y_, depend on the aspect ratio. Setting the aspect ratio
    // necessitates setting v_x_, v_y_
    Vec3d v_x_;
    Vec3d v_y_;
};


#endif //WHITTED_CAMERA_H
