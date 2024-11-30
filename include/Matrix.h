//
// Created by Dustin on 11/29/24.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <string>

#include "Normal.h"
#include "Point.h"
#include "Vector.h"


template<size_t M, size_t N, typename T>
class Matrix {
public:
    Matrix() {
        for(int i = 0; i < M; i++)
            std::memset(data_[i].data(), 0, sizeof (T) * N);
    }

    Matrix(std::initializer_list<T> data) {
        if (data.size() != M * N)
            throw std::logic_error("Must initialize a " + std::to_string(M) +  " by " + std::to_string(N) +
                                    " matrix with " + std::to_string(M*N) + " elements!");

        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] = data[i][j];
    }

    std::array<T, N>& operator[](std::size_t index) {
        if(index >= M || index < 0)
            throw std::logic_error("You must access an element within bounds!");

        return data_[index];
    }

    Matrix<M, N, T>& operator-() {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] *= -1;

        return *this;
    }
    Matrix<M, N, T> operator-() const {
        Matrix<M, N, T> negative;

        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                negative[i][j] *= -data_[i][j];

        return negative;
    }

    Matrix<M, N, T>& operator+=(const Matrix& m);
    Matrix<M, N, T>& operator-=(const Matrix& m);
    Matrix<M, N, T>& operator*(double t);
    Matrix<M, N, T>& operator/(double t);




private:
    std::array<std::array<T, N>, M> data_;
};
template<size_t M, size_t N, typename T>
bool operator==(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2);

template<size_t M, size_t N, typename T>
bool Invertible(const Matrix<M, N, T> m);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> Transpose(const Matrix<M, N, T> m);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> Determinant(const Matrix<M, N, T> m);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> Inverse(const Matrix<M, N, T> m);

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
