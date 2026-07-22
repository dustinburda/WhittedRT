//
// Created by Dustin on 7/20/26.
//

#ifndef WHITTED_IMAGEPLANE_H
#define WHITTED_IMAGEPLANE_H

#include <cstdint>


struct ImagePlane {
    ImagePlane() = delete;

    ImagePlane(std::uint16_t height, std::uint16_t width) : height_{height}, width_{width} {}

    std::uint16_t height_;
    std::uint16_t width_;
};


#endif //WHITTED_IMAGEPLANE_H
