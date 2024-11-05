//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_CAMERA_H
#define WHITTED_CAMERA_H

#include "Point.h"

struct Viewport {
private:
    Point<double, 3> upper_left_corner_;
    Vector<double, 3> x_;
    Vector<double, 3> y_;
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
