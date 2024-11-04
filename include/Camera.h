//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_CAMERA_H
#define WHITTED_CAMERA_H

#include "Point.h"

struct Viewport {

};


class Camera {
public:
    Camera() = delete;
    void GetRayAt(int x, int y) {}

private:
    Point<double, 3> origin_;
    Viewport vp_;

};


#endif //WHITTED_CAMERA_H
