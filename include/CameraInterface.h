//
// Created by Dustin on 12/6/24.
//

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "Ray.h"

class CameraInterface {
public:
    virtual Ray GetRayAt(int x, int y) const = 0;
};

#endif //CAMERAINTERFACE_H
