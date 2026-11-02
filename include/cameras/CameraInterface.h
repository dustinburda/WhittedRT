//
// Created by Dustin on 12/6/24.
//

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "../renderer/ImagePlane.h"
#include "../math/Ray.h"
#include "../samplers/SamplerInterface.h"

#include <memory>

#include "../math/Transformation.h"

class CameraInterface {
public:
    CameraInterface() = delete;
    CameraInterface(Point3D origin, Point3D look_at, Vec3D up);

    virtual ~CameraInterface() = default;

    const Point3D& Origin() const;
    void SetSampler(std::shared_ptr<SamplerInterface> s);

    virtual Ray GetRayAt(std::size_t x, std::size_t y, const ImagePlane& p) const = 0;

protected:
    std::shared_ptr<SamplerInterface> s_;

    Point3D origin_;
    Transformation t_;
};

#endif //CAMERAINTERFACE_H
