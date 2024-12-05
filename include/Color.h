//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_COLOR_H
#define WHITTED_COLOR_H

#include "Globals.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>

// TODO: gamma correction

using COLORREF = std::uint32_t;

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

    Color& operator+=(Color& other) {
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

    COLORREF toRGBA() {
        COLORREF color;

        color |= static_cast<std::uint8_t>(data_[0]) << 16;
        color |= static_cast<std::uint8_t>(data_[1]) << 8;
        color |= static_cast<std::uint8_t>(data_[2]);

        return color;
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

private:
    std::array<double, 4> data_;
};

static bool operator==(const Color& c1, const Color& c2) {
    return std::abs(c1.R() - c2.R()) < epsilon && std::abs(c1.G() - c2.G()) < epsilon  && std::abs(c1.B() - c2.B()) < epsilon;
}

static bool operator!=(const Color& c1, const Color& c2) {
    return !(c1 == c2);
}

static Color operator+(const Color& c1, const Color& c2) {
    Color c;

    c.R() = c1.R() + c2.R();
    c.G() = c1.G() + c2.G();
    c.B() = c1.B() + c2.B();

    return c;
}

static Color operator*(const Color& c1, const Color& c2) {
    Color c;

    c.R() = c1.R() * c2.R();
    c.G() = c1.G() * c2.G();
    c.B() = c1.B() * c2.B();

    return c;
}

static Color operator*(const Color& c1, double t) {
    Color c;

    c.R() = c1.R() * t;
    c.G() = c1.G() * t;
    c.B() = c1.B() * t;

    return c;
}

static Color operator*(double t, const Color& c1) {
    return c1 * t;
}

static Color operator/(const Color& c1, double t) {
    return c1 * (1/t);
}




#endif //WHITTED_COLOR_H
