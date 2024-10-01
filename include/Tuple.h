//
// Created by Dustin on 8/10/24.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <array>
#include <string>
#include <initializer_list>

template<typename T, size_t N>
class Tuple {
public:
    Tuple(std::initializer_list<T>& data) {
        if(data.size() != N) {
            std::string error_msg = "Must intitialize " + std::to_string(N) +
                                    "-tuple with " + std::to_string(N) + " elements, not "
                                    + std::to_string(data.size()) + " elements";
            throw std::logic_error(error_msg);
        }

        for(size_t index = 0; T& element : data) {
            data[index] = element;
            index++;
        }
    }

    T operator[](size_t i) {
        // Fix this
        if(i >= N || i < 0)
            throw std::logic_error("Index must be within bounds!");

        return data_[i];
    }

    Tuple<T, N>& operator-() {
        std::for_each(data_.begin(), data_.end(), [](T& elem) {
            elem = -elem;
        });

        return *this;
    }

    Tuple<T, N>& operator+=(const Tuple<T, N>& other) {
        size_t index = 0;
        std::for_each(data_.begin(), data_.end(), [&other, &index](T& elem){
            elem += other[index];
            index++;
        });

        return *this;
    }

    Tuple<T, N>& operator-=(const Tuple<T, N>& other) {
        return (*this += -other);
    }

    Tuple<T, N>& operator*=(const T& scalar) {
        std::for_each(data_.begin(), data_.end(), [&scalar](T& elem){
            elem *= scalar;
        });

        return *this;
    }

    Tuple<T, N>& operator/=(const T& scalar) {
        return *this *= 1/scalar;
    }

private:
    std::array<T, N> data_;
};

template<typename T, size_t N>
static Tuple<T, N> operator+(const Tuple<T,N>& v1, const Tuple<T, N>& v2) {
    Tuple<T, N> v_plus;
    for(int i = 0; i < N; i++) {
        v_plus[i] = v1[i] + v2[i];
    }

    return v_plus;
}

template<typename T, size_t N>
static Tuple<T, N>operator-(const Tuple<T,N>& v1, const Tuple<T, N>& v2){
    return v1 + (-v2);
}


#endif //TUPLE_H
