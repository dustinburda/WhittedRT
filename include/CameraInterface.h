//
// Created by Dustin on 12/6/24.
//

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "ImagePlane.h"
#include "Ray.h"
#include "Sampler.h"

#include <memory>

class CameraInterface {
public:
    CameraInterface() = delete;

    CameraInterface(Point3D origin, Vec3D look_at_, Vec3D up, double h_fov)
        : origin_{origin}, look_at_{look_at_}, up_{up}, h_fov_{h_fov} {}

    virtual ~CameraInterface() = default;


    const Point3D& Origin() const { return origin_; }
    virtual std::vector<Ray> GetRayAt(int x, int y, const ImagePlane& p) const = 0;
    void SetSampler(std::shared_ptr<Sampler> s) { s_ = s; }

protected:
    std::shared_ptr<Sampler> s_;

    Point3D origin_;
    Vec3D look_at_;
    Vec3D up_;

    double h_fov_;
};

#endif //CAMERAINTERFACE_H
