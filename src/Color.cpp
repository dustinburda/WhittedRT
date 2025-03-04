//
// Created by Advil on 11/3/2024.
//

#include "../include/Color.h"

bool operator==(const Color& c1, const Color& c2) {
    return std::abs(c1.R() - c2.R()) < epsilon && std::abs(c1.G() - c2.G()) < epsilon  && std::abs(c1.B() - c2.B()) < epsilon;
}

bool operator!=(const Color& c1, const Color& c2) {
    return !(c1 == c2);
}

Color operator+(const Color& c1, const Color& c2) {
    Color c;

    c.R() = c1.R() + c2.R();
    c.G() = c1.G() + c2.G();
    c.B() = c1.B() + c2.B();

    return c;
}

Color operator*(const Color& c1, const Color& c2) {
    Color c;

    c.R() = c1.R() * c2.R();
    c.G() = c1.G() * c2.G();
    c.B() = c1.B() * c2.B();

    return c;
}

Color operator*(const Color& c1, double t) {
    Color c;

    c.R() = c1.R() * t;
    c.G() = c1.G() * t;
    c.B() = c1.B() * t;

    return c;
}

Color operator*(double t, const Color& c1) {
    return c1 * t;
}

Color operator/(const Color& c1, double t) {
    return c1 * (1/t);
}