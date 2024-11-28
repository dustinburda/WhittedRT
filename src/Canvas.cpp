//
// Created by Dustin on 8/7/24.
//

#include "../include/Canvas.h"

Canvas::Canvas(uint16_t width, uint16_t height) : width_(width), height_(height) {
    buffer_.resize(width_ * height_);

    std::memset(buffer_.data(), 0, sizeof(Color) * width_ * height_);

    flushed_ = false;
}

void Canvas::SetColorAt(const Color& color, uint16_t i, uint16_t j) {
    if(i >= width_ || i < 0 || j >= height_ || j < 0)
        throw std::logic_error("Array indices must stay in bounds!");

    // std::unique_lock<std::shared_mutex> l(mutex_);
    buffer_[j * width_ + i] = color;
}

Color Canvas::GetColorAt(uint16_t i, uint16_t j) const {
    if(i >= width_ || i < 0 || j >= height_ || j < 0)
        throw std::logic_error("Array indices must stay in bounds!");

    // std::shared_lock<std::shared_mutex> l(mutex_);
    return buffer_[j * width_ + i];
}

void Canvas::Flush(const std::string& filename) {
    auto current_dir = std::filesystem::current_path().parent_path();
    std::string dir = current_dir.string();
    current_dir += (filename.empty()) ? "/image.ppm" : "/" + filename;
    dir = current_dir.string();

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
    flushed_ = true;
}