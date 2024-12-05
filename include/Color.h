//
// Created by Advil on 11/3/2024.
//

#ifndef WHITTED_COLOR_H
#define WHITTED_COLOR_H

#include <cstdint>

class Color {
public:
    Color() : color_{0x00000000} {};
    Color(std::uint8_t R, std::uint8_t G, std::uint8_t B) {
        color_ = 0x00000000;

    }
private:
    std::uint32_t color_;
};


#endif //WHITTED_COLOR_H
