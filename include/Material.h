//
// Created by Advil on 11/20/2024.
//

#ifndef WHITTED_MATERIAL_H
#define WHITTED_MATERIAL_H

#include "Canvas.h"

struct Material {
    Material(Color color) : color_{color} {}
    Color color_;
};


#endif //WHITTED_MATERIAL_H
