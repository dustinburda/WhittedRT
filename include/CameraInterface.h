//
// Created by Dustin on 12/6/24.
//

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "Ray.h"
#include "Sampler.h"

class CameraInterface {
public:
    virtual std::vector<Ray> GetRayAt(int x, int y) const = 0;
    void SetSampler(std::shared_ptr<Sampler> s) { s_ = s; }

protected:
    std::shared_ptr<Sampler> s_;
};

#endif //CAMERAINTERFACE_H
