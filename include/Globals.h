//
// Created by Advil on 11/23/2024.
//

#ifndef WHITTED_GLOBALS_H
#define WHITTED_GLOBALS_H

constexpr double epsilon = 10e-3;
constexpr double pi = 3.14159265358979323846;
constexpr double infinity = std::numeric_limits<double>::infinity();

// User-defined literal: Degrees
template<typename T, T...>
T operator ""_deg();


// User-defined literal: Radians
template<typename T, T...>
T operator  ""_rad();

#endif //WHITTED_GLOBALS_H

