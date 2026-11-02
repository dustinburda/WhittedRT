//
// Created by Dustin on 2/20/25.
//

#ifndef WHITTED_TEXTURE_H
#define WHITTED_TEXTURE_H

#include "../util/Color.h"
#include "../math/Point.h"

#include "../../lib/stb_image.h"

#include <filesystem>
#include <fstream>
#include <vector>

class TextureInterface {
public:
    virtual ~TextureInterface();
    virtual Color GetTexel(Point2D texture_coordinates) = 0;
};

class ImageTexture : public TextureInterface {
public:
    ImageTexture(std::string& filename) {
        int x;
        int y;
        unsigned char* bitmap_data = stbi_load(filename.data(), &x, &y, nullptr, 3);
        // defensive programming

        num_cols_ = x;
        num_rows_ = y;

        // write data to bitmap

        stbi_image_free(bitmap_data);
    }

    Color GetTexel(Point2D) override {
        return Color{};
    }

    ~ImageTexture() override;
private:
    std::vector<std::vector<Color>> bitmap_;
    std::size_t num_rows_;
    std::size_t num_cols_;
};

class CheckerTexture : public TextureInterface {
public:
    ~CheckerTexture() override;

    Color GetTexel(Point2D) override {
        return Color{};
    }
};

class NoiseTexture : public TextureInterface {
public:
    ~NoiseTexture() override;

    Color GetTexel(Point2D) override {
        return Color{};
    }
};

#endif //WHITTED_TEXTURE_H
