//
// Created by Advil on 11/18/2024.
//

#ifndef WHITTED_SHADECONTEXT_H
#define WHITTED_SHADECONTEXT_H

#include "Canvas.h"
#include "Normal.h"
#include "Point.h"

#include <memory>
#include <limits>

class MaterialInterface;

struct ShadeContext {
    // TODO: expand
    Normal<double, 3> normal_;
    Point<double, 3> point_;
    std::shared_ptr<MaterialInterface> mat_;
    double t_min_ = 0;
    double t_max_ = std::numeric_limits<double>::max();

    Point2D uv_;
};


#endif //WHITTED_SHADECONTEXT_H
