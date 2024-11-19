//
// Created by Advil on 11/18/2024.
//

#ifndef WHITTED_SHADECONTEXT_H
#define WHITTED_SHADECONTEXT_H

#include "Normal.h"
#include "Canvas.h"

struct ShadeContext {
    // TODO: expand
    Normal<double, 3> normal_;
    Color color_;
};


#endif //WHITTED_SHADECONTEXT_H
