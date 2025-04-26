//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_UTIL_H
#define WHITTED_UTIL_H

#include <limits>
#include <random>

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

static int RandomInt(int min = 0, int max = std::numeric_limits<int>::max()) {
    std::random_device rd;
    std::mt19937 gen{rd()};

    std::uniform_int_distribution distribution{min, max};

    return distribution(gen);
}

static double RandomDouble(double min = 0, double max = std::numeric_limits<double>::max()) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<double> distribution{min, max};
    return distribution(gen);
}

#endif //WHITTED_UTIL_H

