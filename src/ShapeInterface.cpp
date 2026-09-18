//
// Created by Dustin on 9/18/26.
//

#include "../include/ShapeInterface.h"

ShapeInterface::ShapeInterface(ShapeType type) : type_(type) {}

ShapeType ShapeInterface::Type() const { return type_; }
