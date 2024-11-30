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

    Matrix<M, N, T>& operator+=(const Matrix& m) {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] += m[i][j];

        return *this;
    }

    Matrix<M, N, T>& operator-=(const Matrix& m) {
        *this += (-m);
        return *this;
    }

    Matrix<M, N, T>& operator*(double t) {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] *= t;
    }

    Matrix<M, N, T>& operator/(double t) {
        *this *= (1.0 / t);

        return *this;
    }

private:
    std::array<std::array<T, N>, M> data_;
};

template<size_t M, size_t N, typename T>
static bool operator==(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            if(m1[i][j] != m2[i][j])
                return false;

    return true;
}

template<size_t M, size_t N, typename T>
static bool operator!=(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
    return !(m1 == m2);
}

template<size_t N, typename T>
static Matrix<N, N, T> Identity() {
    Matrix<N, N, T> identity;

    for(int i = 0; i < N; i++)
        identity[i][i] = 1;

    return identity;
}

template<size_t N, typename T>
static bool Invertible(const Matrix<N, N, T> m) {
    return Determinant(m) != 0;
}

template<size_t M, size_t N, typename T>
static Matrix<N, M, T> Transpose(const Matrix<M, N, T> m) {
    Matrix<N, M, T> transpose;

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            transpose[j][i] = m[i][j];

    return transpose;
}

template<size_t N, typename T>
static Matrix<N, N, T> Determinant(const Matrix<N, N, T> m);

template<size_t N, typename T>
static Matrix<N, N, T> Inverse(const Matrix<N, N, T> m);

template<size_t M, size_t N, typename T>
static Matrix<M, N, T> operator+(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
    Matrix<M, N, T> sum;

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            sum[i][j] = m1[i][j] + m2[i][j];

    return sum;
}

template<size_t M, size_t N, typename T>
static Matrix<M, N, T> operator-(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
    return m1 + (-m2);
}

template<size_t M, size_t N, typename T>
static Matrix<M, N, double> operator*(const Matrix<M, N, T>& m, double t) {
    Matrix<M, N, double> mult;

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            mult[i][j] *= static_cast<double>(t);

    return mult;
}

template<size_t M, size_t N, typename T>
static Matrix<M, N, double> operator*(double t, const Matrix<M, N, T>& m) {
    return m * t;
}

template<size_t M, size_t N, typename T>
static Matrix<M, N, double> operator/(const Matrix<M, N, T>& m, double t) {
    return m * (1.0 / t);
}

template<size_t M, size_t N, typename T>
static Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Normal<T, N>& n);

template<size_t M, size_t N, typename T>
static Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Point<T, N>& p);

template<size_t M, size_t N, typename T>
static Matrix<M, N, T> operator*(const Matrix<M, N, T>& m, const Vector<T, N>& v);

template<size_t M, size_t N, size_t K, typename T>
static Matrix<M, K, T> operator*(const Matrix<M, N, T>& m1, const Matrix<N, K, T>& m2);






#endif //MATRIX_H
