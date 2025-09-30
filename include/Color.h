//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_COLOR_H
#define WHITTED_COLOR_H

#include "Util.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>

// TODO: gamma correction

class Color {
public:
    Color() { std::memset(data_.data(), 0, sizeof(double) * 4); };
    Color(double R, double G, double B) {
        data_[0] = R;
        data_[1] = G;
        data_[2] = B;
    }

    double R() const { return data_[0]; }
    double G() const { return data_[1]; }
    double B() const { return data_[2]; }

    double& R() { return data_[0]; }
    double& G() { return data_[1]; }
    double& B() { return data_[2]; }

    double operator[](std::size_t i) {
        if (i >= 3 || i < 0)
            throw std::logic_error("Color only has three components!");

        return data_[i];
    }

    Color& operator+=(const Color& other) {
        data_[0] += other.data_[0];
        data_[1] += other.data_[1];
        data_[2] += other.data_[2];

        return *this;
    }

    Color& operator*=(double t) {
        data_[0] *= t;
        data_[1] *= t;
        data_[2] *= t;

        return *this;
    }

    Color& operator/=(double t) {
        (*this) *= (1/t);
        return (*this);
    }

    std::string toString() {
        std::stringstream s;

        s << "Color: [\n";
        s << "R: " << data_[0] << " ";
        s << "G: " << data_[1] << " ";
        s << "B: " << data_[2];
        s << "]";

        return s.str();
    }

    static double sRGBToLinear(double sRGB);
    double GrayScale() const;

private:
    std::array<double, 4> data_;
};

bool operator==(const Color& c1, const Color& c2);
bool operator!=(const Color& c1, const Color& c2);
Color operator+(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator*(const Color& c1, double t);
Color operator/(const Color& c1, double t);
Color operator*(double t, const Color& c1);




#endif //WHITTED_COLOR_H
