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
#include <shared_mutex>
#include <sstream>
#include <vector>

// TODO TEST THIS
#include "Color.h"

class Canvas {
public:

	explicit Canvas(uint16_t width, uint16_t height);
	~Canvas() {
        if(!flushed_)
		    Flush();
	}

	void SetColorAt(const Color& color, uint16_t i, uint16_t j);
	Color GetColorAt(uint16_t i, uint16_t j) const;
	void Flush(const std::string& path = "");

private:

	const uint16_t width_;
	const uint16_t height_;
	std::vector<Color> buffer_;
    bool flushed_;
	// mutable std::shared_mutex mutex_;
};

#endif //CANVAS_H
