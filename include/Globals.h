//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_GLOBALS_H
#define WHITTED_GLOBALS_H

constexpr double epsilon = 10e-3;
constexpr double pi = 3.14159265358979323846;
constexpr double infinity = std::numeric_limits<double>::infinity();

struct deg {
    long double degrees;
};

// User-defined literal: Degrees
static deg operator ""_deg(long double degrees) { return deg{degrees}; };

struct rad {
    long double radians;
};

// User-defined literal: Radians
static rad operator  ""_rad(long double radians) { return rad{radians}; };

#endif //WHITTED_GLOBALS_H

