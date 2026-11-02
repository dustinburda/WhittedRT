//
// Created by Dustin on 8/7/24.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <vector>

// TODO TEST THIS
#include "Color.h"

class Canvas {
public:

	explicit Canvas(std::size_t width, std::size_t height);
	~Canvas() {
        if(!flushed_)
		    Flush();
	}

	void SetColorAt(const Color& color, std::size_t i, std::size_t j);
	Color GetColorAt(std::size_t i, std::size_t j) const;
	void Flush(const std::string& path = "");

	std::size_t Width() const { return width_; }
	std::size_t Height() const { return height_; }

private:

	const std::size_t width_;
	const std::size_t height_;
	std::vector<Color> buffer_;
    bool flushed_;

	mutable std::shared_mutex mutex_;
};

#endif //CANVAS_H
