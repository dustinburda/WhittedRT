//
// Created by Dustin on 11/5/26.
//

#ifndef WHITTED_TRACE_H
#define WHITTED_TRACE_H

#include "Color.h"
#include "../parsers/SceneParser.h"

Color Trace(const Scene& scene, Ray& r, ShadeContext& context);

#endif //WHITTED_TRACE_H
