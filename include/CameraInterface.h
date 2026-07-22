//
// Created by Dustin on 12/6/24.
//

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "ImagePlane.h"
#include "Ray.h"
#include "Sampler.h"

class CameraInterface {
public:
    CameraInterface() = delete;

    CameraInterface(Point3d origin, Vec3d look_at_, Vec3d up, double h_fov)
        : origin_{origin}, look_at_{look_at_}, up_{up}, h_fov_{h_fov} {}


    const Point3d& Origin() const { return origin_; }
    virtual std::vector<Ray> GetRayAt(int x, int y, const ImagePlane& p) const = 0;
    void SetSampler(std::shared_ptr<Sampler> s) { s_ = s; }

protected:
    std::shared_ptr<Sampler> s_;

    Point3d origin_;
    Vec3d look_at_;
    Vec3d up_;

    double h_fov_;
};

#endif //CAMERAINTERFACE_H
