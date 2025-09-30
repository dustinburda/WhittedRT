//
// Created by Dustin on 11/29/24.
//

#ifndef MATRIX_H
#define MATRIX_H

#include "Normal.h"
#include "Point.h"
#include "Vector.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <sstream>


template<typename T, std::size_t M, std::size_t N>
class Matrix {
public:
    Matrix() {
        for(std::size_t i = 0; i < M; i++)
            std::memset(data_[i].data(), 0, sizeof (T) * N);
    }

    Matrix(std::initializer_list<T> data) {
        if (data.size() != M * N)
            throw std::logic_error("Must initialize a " + std::to_string(M) +  " by " + std::to_string(N) +
                                    " matrix with " + std::to_string(M*N) + " elements!");

        for(int index = 0; T num : data) {
            int i = index / N;
            int j = index % N;
            data_[i][j] = num;
            index++;
        }
    }

    std::array<T, N>& operator[](std::size_t index) {
        if(index >= M || index < 0)
            throw std::logic_error("You must access an element within bounds!");

        return data_[index];
    }

    std::array<T, N> operator[](std::size_t index) const {
        if(index >= M || index < 0)
            throw std::logic_error("You must access an element within bounds!");

        return data_[index];
    }

    Matrix<T, M, N>& operator-() {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] *= -1;

        return *this;
    }
    Matrix<T, M, N> operator-() const {
        Matrix<T, M, N> negative;

        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                negative[i][j] *= -data_[i][j];

        return negative;
    }

    Matrix<T, M, N>& operator+=(const Matrix& m) {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] += m[i][j];

        return *this;
    }

    Matrix<T, M, N>& operator-=(const Matrix& m) {
        *this += (-m);
        return *this;
    }

    Matrix<T, M, N>& operator*(double t) {
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                data_[i][j] *= t;
    }

    Matrix<T, M, N>& operator/(double t) {
        *this *= (1.0 / t);

        return *this;
    }

    std::string toString() const
    {
        std::stringstream ss;

        ss << "Matrix: [\n";
        for(int i = 0; i < M; i++) {
            ss << "[";
            for(int j = 0; j < N; j++) {
                ss << data_[i][j];
                if (j != N - 1)
                    ss << ", ";
            }
            ss<< "]\n";
        }
        ss << "]";

        return ss.str();
    }

private:
    std::array<std::array<T, N>, M> data_;
};

template<typename T, size_t M, size_t N>
static bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            if(m1[i][j] != m2[i][j])
                return false;

    return true;
}

template<typename T, size_t M, size_t N>
static bool operator!=(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    return !(m1 == m2);
}

template<typename T, size_t N>
static Matrix<T, N, N> Identity() {
    Matrix<T, N, N> identity;

    for(int i = 0; i < N; i++)
        identity[i][i] = 1;

    return identity;
}

template<typename T, size_t N>
static bool Invertible(const Matrix<T, N, N> m) {
    return Determinant(m) != 0;
}

template<typename T, size_t M, size_t N>
static Matrix<T, N, M> Transpose(const Matrix<T, M, N> m) {
    Matrix<T, N, M> transpose;

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            transpose[j][i] = m[i][j];

    return transpose;
}

template<typename T, size_t N>
static Matrix<T, N, N> Determinant(const Matrix<T, N, N> m) {
    Matrix<T, N, N> copy = m;

    for(int r = 0; r < N; r++) {
        for(int r_next = r + 1; r_next < N; r_next++) {
            double f = copy[r_next][r] / copy[r][r];
            for(int c = r; c < N; c++) {
                copy[r_next][c] -= f * copy[r][c];
            }
        }
    }

    double det = 1;
    for(int i = 0; i < N; i++)
        det *= copy[i][i];

    return det;
}

template<typename T, size_t N>
static Matrix<T, N, N> Inverse(const Matrix<T, N, N> m) {
    Matrix<T, N,2*N> augmented;
    for(std::size_t i = 0; i < N; i++) {
        for(std::size_t j = 0; j < N; j++) {
            augmented[i][j] = m[i][j];
        }
    }

    for(std::size_t i = 0; i < N; i++)
        augmented[i][i+N] = 1;
    for(std::size_t i = 0; i < N -1; i++) {
        for(int  j = 2*N -1; j >= 0; j--) {
            augmented[i][j] /= augmented[i][i];
        }
        for(std::size_t k = i + 1; k < N; k++) {
            float coeff = augmented[k][i];
            for(std::size_t j = 0; j < 2*N; j++) {
                augmented[k][j] -= augmented[i][j] * coeff;
            }
        }
    }

    for(int j = 2*N -1; j >= N - 1; j--)
        augmented[N-1][j] /= augmented[N-1][N-1];
    // second pass
    for (int i = N -1; i > 0; i--) {
        for (int k= i -1; k >= 0; k--) {
            float coeff = augmented[k][i];
            for (std::size_t j=0; j < 2*N; j++) {
                augmented[k][j] -= augmented[i][j] * coeff;
            }
        }
    }

    Matrix<T, N, N> inverse;

    for(std::size_t i = 0; i < N; i++) {
        for(std::size_t j = 0; j < N; j++) {
            inverse[i][j] = augmented[i][j + N];
        }
    }

    return inverse;
}

template<typename T, size_t M, size_t N>
static Matrix<T, M, N> operator+(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    Matrix<T, M, N> sum;

    for(std::size_t i = 0; i < M; i++)
        for(std::size_t j = 0; j < N; j++)
            sum[i][j] = m1[i][j] + m2[i][j];

    return sum;
}

template<typename T, size_t M, size_t N>
static Matrix<T, M, N> operator-(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    return m1 + (-m2);
}

template<typename T, size_t M, size_t N>
static Matrix<double, M, N> operator*(const Matrix<T, M, N>& m, double t) {
    Matrix<double, M, N> mult;

    for(std::size_t i = 0; i < M; i++)
        for(std::size_t j = 0; j < N; j++)
            mult[i][j] = m[i][j] * static_cast<double>(t);

    return mult;
}

template<typename T, size_t M, size_t N>
static Matrix<double, M, N> operator*(double t, const Matrix<T, M, N>& m) {
    return m * t;
}

template<typename T, size_t M, size_t N>
static Matrix<double, M, N> operator/(const Matrix<T, M, N>& m, double t) {
    return m * (1.0 / t);
}

template<size_t M, size_t N, typename T>
static Vector<T, N> operator*(const Matrix<T, M, N>& m, const Vector<T, N>& v) {
    Vector<T, N> v_mult;

    for(std::size_t i = 0; i < N; i++) {
        double dot = 0;
        for(std::size_t j = 0; j < N; j++)
            dot += m[i][j] * v[j];
        v_mult[i] = dot;
    }
    return v_mult;
}

template<typename T, size_t M, size_t N, size_t K>
static Matrix<T, M, K> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, K>& m2) {
    Matrix<T, M, K> mult;

    for(std::size_t i = 0; i < M; i++) {
        for(std::size_t j = 0; j < K; j++) {
            double dot = 0;
            for(std::size_t l = 0; l < N; l++) {
                dot += m1[i][l] * m2[l][j];
            }
            mult[i][j] = dot;
        }
    }

    return mult;
}


using Mat4d = Matrix<double, 4,4>;
using Mat4i = Matrix<int, 4, 4>;
using Mat3d = Matrix<double, 3, 3>;
using Mat3i = Matrix<int, 3, 3>;




#endif //MATRIX_H
