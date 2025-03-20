//
// Created by Advil on 11/18/2024.
//

#ifndef WHITTED_SHADECONTEXT_H
#define WHITTED_SHADECONTEXT_H

#include "Canvas.h"
#include "Normal.h"
#include "Material.h"
#include "Point.h"

#include <memory>
#include <limits>

using TextureCoordinates = std::pair<Point2d, Point2d>;

struct ShadeContext {
    // TODO: expand
    Normal<double, 3> normal_;
    Point<double, 3> point_;
    std::shared_ptr<Material> mat_;
    double t_min_ = 0;
    double t_max_ = std::numeric_limits<double>::max();

    TextureCoordinates uv_;
};


#endif //WHITTED_SHADECONTEXT_H
