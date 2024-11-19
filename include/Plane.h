//
// Created by Advil on 11/6/2024.
//

#ifndef WHITTED_PLANE_H
#define WHITTED_PLANE_H

#include "Shape.h"
#include "Point.h"
#include "Normal.h"

class Plane : public Shape {
public:

private:
    Point<double, 3> point_;
    Normal<double, 3> normal_;
};


#endif //WHITTED_PLANE_H
