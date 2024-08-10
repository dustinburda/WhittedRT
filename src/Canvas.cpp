//
// Created by Dustin on 8/7/24.
//

#include "../include/Canvas.h"


Canvas::Canvas(uint16_t width, uint16_t height) : width_(width), height_(height) {
    buffer_.resize(width_ * height_);

    std::memset(buffer_.data(), 0, sizeof(Color) * width_ * height_);
}

void Canvas::SetColorAt(const Color& color, uint16_t i, uint16_t j) {
    if(i >= height_ || i < 0 || j >= width_ || j < 0)
        throw std::logic_error("Array indices must stay in bounds!");

    buffer_[i * width_ + j] = color;
}

Color Canvas::GetColorAt(uint16_t i, uint16_t j) const {
    if(i >= height_ || i < 0 || j >= width_ || j < 0)
        throw std::logic_error("Array indices must stay in bounds!");

    return buffer_[i * width_ + j];
}

void Canvas::Flush(const std::string& filename) {
    auto current_dir = std::filesystem::current_path().parent_path();
    std::string dir = current_dir;
    current_dir += (filename.empty()) ? "/image.ppm" : filename;
    dir = current_dir;

    std::stringstream image_content;

    image_content << "P3\n";
    image_content << std::to_string(width_) +  " " + std::to_string(height_) + "\n";
    image_content << std::to_string(255) + "\n";

    for(auto& color : buffer_) {
        image_content << std::to_string(static_cast<uint8_t>(color[0] * 255)) + " "
                       + std::to_string(static_cast<uint8_t>(color[1] * 255)) + " "
                       + std::to_string(static_cast<uint8_t>(color[2] * 255)) + "\n";
    }

    std::ofstream image { current_dir };
    if(!image.is_open()) {
        std::cerr << "Image failed to open!";
    }
    image << image_content.rdbuf();

    image.flush();
}