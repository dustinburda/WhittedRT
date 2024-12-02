//
// Created by Dustin on 12/1/24.
//

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


#include "Matrix.h"
#include "Normal.h"
#include "Point.h"
#include "Vector.h"

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

    Matrix<double, 4, 4>& Transform() { return transform_; }
    Matrix<double, 4, 4>& InverseTransform() { return inverse_transform_; }
private:
    Transformation() = default;


    Matrix<double, 4, 4> transform_;
    Matrix<double, 4, 4> inverse_transform_;
};


static Vector<double, 3> operator*(Transformation& t, const Vector<double, 3>& v) {
    Vector<double, 4> homogenous_v = v.Homogenize();
    homogenous_v = t.Transform() * homogenous_v;

    return homogenous_v.DeHomogenize();
}

static Point<double, 3> operator*(Transformation& t, const Point<double, 3>& p) {
    Vector<double, 4> homogenous_v = p.Homogenize().ToVector(); // p1, p2, p3, 1
    homogenous_v = t.Transform() * homogenous_v; // mp1, mp2, mp3, 1

    Point<double, 4> homogenous_point {homogenous_v[0], homogenous_v[1], homogenous_v[2], homogenous_v[3]};

    return homogenous_point.DeHomogenize();
}

static Normal<double, 3> operator*(Transformation& t, const Normal<double, 3>& n) {
    Vector<double, 4> homogenous_v = n.Homogenize().ToVector(); // n1, n2, n3, 0
    homogenous_v = Transpose(t.InverseTransform()) * homogenous_v; // mn1, mn2, mn3, 0

    Normal<double, 4> homogenous_normal {homogenous_v[0], homogenous_v[1], homogenous_v[2], homogenous_v[3]};

    return homogenous_normal.DeHomogenize();
}

#endif //TRANSFORMATION_H
