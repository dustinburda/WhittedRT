//
// Created by Dustin on 12/6/24.
//

#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "CameraInterface.h"

class OrthographicCamera : public CameraInterface {
public:
    OrthographicCamera() = delete;
    OrthographicCamera(int width, int height)
        : aspect_ratio_{static_cast<double>(width) / static_cast<double>(height) }, v_x_ {2.0 * aspect_ratio_ / width, 0.0, 0.0}, v_y_{0.0, 2.0 * (-1.0) / height, 0.0} {}
    Ray GetRayAt(int x, int y) const override;

private:
    double aspect_ratio_;
    // Note v_x_, v_y_, depend on the aspect ratio. Setting the aspect ratio
    // necessitates setting v_x_, v_y_
    Vec3d v_x_;
    Vec3d v_y_;
};



#endif //ORTHOGRAPHICCAMERA_H
