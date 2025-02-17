//
// Created by Dustin on 8/10/24.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <algorithm>
#include <array>
#include <cstring>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>


template<typename T, size_t N>
class Vector {
public:
     Vector() { std::memset(data_.data(), 0, N * sizeof (T)); }

     Vector(const std::initializer_list<T>& data) {
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

    Vector(const Vector<T, N - 1>& v, T val) {
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

    Vector<T, N> operator-() const {
        Vector<T, N> negative;

        for(std::size_t i = 0; i < N; i++)
            negative[i] = -data_[i];

        return negative;
    }

    Vector<T, N>& operator+=(const Vector<T, N>& other) {
        size_t index = 0;
        std::for_each(data_.begin(), data_.end(), [&other, &index](T& elem){
            elem += other[index];
            index++;
        });

        return *this;
    }

    Vector<T, N>& operator-=(const Vector<T, N>& other) {
        return (*this += -other);
    }

    Vector<T, N>& operator*=(const T& scalar) {
        std::for_each(data_.begin(), data_.end(), [&scalar](T& elem){
            elem *= scalar;
        });

        return *this;
    }

    Vector<T, N>& operator/=(const T& scalar) {
        return *this *= 1/scalar;
    }


    double LengthSquared() const {
         double magnitude = 0;
         for(std::size_t i = 0; i < N; i++){
             magnitude += data_[i] * data_[i];
         }

         return magnitude;
    }

    double Length() const {
         return std::sqrt(LengthSquared());
     }

    Vector<T, N> UnitVector() const {
         return (*this) / Length();
    }


    std::string toString() const
    {
         std::stringstream ss;

         ss << "Vector: [";
         for(std::size_t i = 0; i < N; i++)
         {
             ss << " " <<  data_[i];
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
static Vector<T, N> operator+(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    Vector<T, N> v_plus;
    for(std::size_t i = 0; i < N; i++) {
        v_plus[i] = v1[i] + v2[i];
    }

    return v_plus;
}

template<typename T, size_t N>
static Vector<T, N>operator-(const Vector<T,N>& v1, const Vector<T, N>& v2){
    return v1 + (-v2);
}

template<typename T, size_t N>
static Vector<double, N> operator*(const Vector<T,N>& v1, const double t) {
    Vector<double, N> v;
    for(std::size_t i = 0; i < N; i++) {
        v[i] = static_cast<double>(v1[i]) * t;
    }

    return v;
}

template<typename T, size_t N>
static Vector<double, N> operator*(const double t, const Vector<T,N>& v1) {
    return v1 * t;
}

template<typename T, size_t N>
static Vector<double, N> operator/(const Vector<T,N>& v1, const double t) {
    return v1 * (1/t);
}


template<typename T, size_t N>
static bool operator==(const Vector<T, N>& v1, Vector<T,N> &v2){
    for(int i = 0; i < N; i++){
        if(v1[i] != v2[i])
            return false;
    }

    return true;
}

template<typename T, size_t N>
static double Dot(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    double dot_product = 0;
    for(size_t i = 0; i < N; i++) {
        dot_product += v1[i] * v2[i];
    }

    return dot_product;
}

template<typename  T, size_t N = 3>
static Vector<T, N> Cross(const Vector<T,N>& v1, const Vector<T, N>& v2) {
    if (N != 3)
        throw std::logic_error("The cross product is defined for vectors of dimension 3!");

    Vector<T, N> cross_product = {
            v1[1] * v2[2] - v1[2] * v2[1],
            v2[0] * v1[2] - v1[0] * v2[2],
            v1[0] * v2[1] - v1[1] * v2[0]
    };

    return cross_product;
}

template<typename T, size_t N>
static bool operator==(const Vector<T,N>& v1, const Vector<T, N>& v2)
{
    for(int i = 0; i < N; i++)
    {
        if(v1[i] != v2[i])
            return false;
    }

    return true;
}

// IN RADIANS
template<typename T, size_t N>
static double Angle(const Vector<T, N>& v1, const Vector<T, N>& v2)
{
    double dot_product = dot(v1, v2);
    double cos_theta = dot_product / (v1.length() * v2.length());

    return acos(cos_theta);
}


using Vec4f = Vector<float, 4>;
using Vec4d = Vector<double, 4>;
using Ve4i = Vector<int, 4>;
using Vec3f = Vector<float, 3>;
using Vec3d = Vector<double, 3>;
using Ve3i = Vector<int, 3>;
using Vec2f = Vector<float, 2>;
using Vec2d = Vector<double, 2>;
using Ve2i = Vector<int, 2>;




#endif //TUPLE_H
