//
// Created by Dustin Burda on 10/5/24.
//

#ifndef WHITTED_NORMAL_H
#define WHITTED_NORMAL_H

#include "Vector.h"
#include "Point.h"

#include <cstring>
#include <string>
#include <sstream>

template<typename T, size_t N>
class Normal {
public:
    Normal() { std::memset(data_.data(), 0, N * sizeof (T)); }

    Normal(const std::initializer_list<T>& data) {
        if(data.size() != N) {
            std::string error_msg = "Must initialize " + std::to_string(N) +
                                    "-tuple with " + std::to_string(N) + " elements, not "
                                    + std::to_string(data.size()) + " elements";
            throw std::logic_error(error_msg);
        }

        // Pad with zeroes
        std::memset(data_.data(), 0, N * sizeof (T));

        for(size_t index = 0; const T& element : data) {
            data_[index] = element;
            index++;
        }
    }

    Normal(const Normal<T, N - 1>& v, T val) {
        std::memcpy(data_.data(), v.data_.data(), (N - 1) * sizeof(T));
        data_[N - 1] = val;
    }

    T& operator[](size_t i) {
        if(i >= N || i < 0)
            throw std::logic_error("Index must be within bounds!");

        return data_[i];
    }

    T operator[](size_t i) const {
        if(i >= N || i < 0)
            throw std::logic_error("Index must be within bounds!");

        return data_[i];
    }

    Normal<T, N> operator-() const {
        Normal<T, N> negative;

        for(int i = 0; i < N; i++)
            negative[i] = -data_[i];

        return negative;
    }

    Normal<T, N>& operator+=(const Normal<T, N>& other) {
        size_t index = 0;
        std::for_each(data_.begin(), data_.end(), [&other, &index](T& elem){
            elem += other[index];
            index++;
        });

        return *this;
    }

    Normal<T, N>& operator*=(const T& scalar) {
        std::for_each(data_.begin(), data_.end(), [&scalar](T& elem){
            elem *= scalar;
        });

        return *this;
    }

    Normal<T, N>& operator/=(const T& scalar) {
        return *this *= 1/scalar;
    }


    double LengthSquared() const {
        double magnitude = 0;
        for(int i = 0; i < N; i++){
            magnitude += data_[i] * data_[i];
        }

        return magnitude;
    }

    double Length() const {
        return std::sqrt(LengthSquared());
    }

    Normal<T, N> UnitNormal() const {
        return (*this) / Length();
    }

    Vector<T, N> ToVector() const {
        Vector<T, N> v;

        for(int i = 0; i < N - 1; i++)
            v[i] = data_[i];

        return v;
    }

    std::string toString() const {
        std::stringstream ss;

        ss << "Normal : [";

        for(int i = 0; i < N; i++) {
            ss << data_[i];
            if (i != N - 1)
                ss << ", ";
        }

        ss << "]";

        return ss.str();
    }
private:
    std::array<T, N> data_;
};


template<typename T, size_t N>
static Normal<T, N> operator+(const Normal<T,N>& n1, const Normal<T, N>& n2) {
    Normal<T, N> n_plus;
    for(int i = 0; i < N; i++) {
        n_plus[i] = n1[i] + n2[i];
    }

    return n_plus;
}

template<typename T, size_t N>
static double Dot(const Vector<T,N>& v, const Normal<T, N>& n) {
    double dot_product = 0;
    for(size_t i = 0; i < N; i++) {
        dot_product += v[i] * n[i];
    }

    return dot_product;
}

template<typename T, size_t N>
static double Dot(const Normal<T,N>& n, const Vector<T, N>& v) {
    double dot_product = 0;
    for(size_t i = 0; i < N; i++) {
        dot_product += v[i] * n[i];
    }

    return dot_product;
}


template<typename T, size_t N>
static Normal<double, N> operator*(const Normal<T,N>& n, const double t) {
    Normal<double, N> n_scalar;
    for(int i = 0; i < N; i++) {
        n_scalar[i] = static_cast<double>(n[i]) * t;
    }

    return n_scalar;
}

template<typename T, size_t N>
static Normal<double, N> operator*(const double t, const Normal<T,N>& n) {
    return n * t;
}

template<typename T, size_t N>
static Normal<double, N> operator/(const Normal<T,N>& n, const double t) {
    return n * 1/t;
}

template<typename T, size_t N>
static Vector<T, N> operator+(const Normal<T,N>& n, const Vector<T, N>& v) {
    Vector<T, N> v_plus;
    for(int i = 0; i < N; i++) {
        v_plus[i] = n[i] + v[i];
    }

    return v_plus;
}

template<typename T, size_t N>
static Vector<T, N> operator+(const Vector<T, N>& v, const Normal<T,N>& n) {
    Vector<T, N> v_plus;
    for(int i = 0; i < N; i++) {
        v_plus[i] = n[i] + v[i];
    }

    return v_plus;
}

#endif //WHITTED_NORMAL_H
