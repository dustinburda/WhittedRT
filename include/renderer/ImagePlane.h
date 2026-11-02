//
// Created by Dustin on 7/20/26.
//

#ifndef WHITTED_IMAGEPLANE_H
#define WHITTED_IMAGEPLANE_H

#include <cstddef>


struct ImagePlane {
    ImagePlane() = delete;

    ImagePlane(std::size_t height, std::size_t width) : height_{ height }, width_{ width } {}

    std::size_t height_;
    std::size_t width_;
};


#endif //WHITTED_IMAGEPLANE_H
