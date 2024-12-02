//
// Created by Dustin on 12/1/24.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include "Shape.h"
#include "Transformations.h"

#include <memory>

class Instance : public Shape {
public:

private:
    Transformation* t_;
    std::shared_ptr<Shape> shape_;
};



#endif //INSTANCE_H
