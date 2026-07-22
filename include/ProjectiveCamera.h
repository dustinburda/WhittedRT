//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_CAMERA_H
#define WHITTED_CAMERA_H

#include "CameraInterface.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

#include <cstdint>

class ProjectiveCamera : public CameraInterface {
public:
    ProjectiveCamera(Point3d origin, Vec3d look_at_, Vec3d up, double h_fov)
        : CameraInterface(origin, look_at_, up, h_fov) {}

    std::vector<Ray> GetRayAt(int x, int y, const ImagePlane& p) const override;
};


#endif //WHITTED_CAMERA_H
