//
// Created by Dustin on 11/29/24.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cstdint>
#include <initializer_list>

#include "Normal.h"
#include "Point.h"
#include "Vector.h"


template<size_t M, size_t N, typename T>
class Matrix {
public:
    Matrix() = default;
    Matrix(std::initializer_list<T> data) {}

    T operator[](std::size_t index);

    Matrix<M, N, T>& operator-();
    Matrix<M, N, T> operator-() const;

    Matrix<M, N, T>& operator+=(const Matrix& m);
    Matrix<M, N, T>& operator*(double t);


private:
    std::array<std::array<T, N>, M> data_;
};


template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator-(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, double t);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator*(double t, const Matrix<M, N, T>& m);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Normal<T, N>& n);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Point<T, N>& p);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Vector<T, N>& v);







#endif //MATRIX_H
