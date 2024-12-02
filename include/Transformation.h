//
// Created by Dustin on 12/1/24.
//

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


#include "Matrix.h"

class Transformation : public Matrix<double,4,4> {
public:
    static Transformation Translation(double x, double y, double z);

     static Transformation RotationX(double radians);
     static Transformation RotationY(double radians);
     static Transformation RotationZ(double radians);

     static Transformation ReflectionX();
     static Transformation ReflectionY();
     static Transformation ReflectionZ();

    static Transformation Scale(double x, double y, double z);
private:
    Transformation() = default;
    Matrix<double, 4, 4>& Transform() { return transform_; }
    Matrix<double, 4, 4>& InverseTransform() { return inverse_transform_; }


    Matrix<double, 4, 4> transform_;
    Matrix<double, 4, 4> inverse_transform_;
};



#endif //TRANSFORMATION_H
