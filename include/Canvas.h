//
// Created by Dustin on 8/7/24.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <cstdint>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <array>
#include <vector>

using Color = std::array<uint8_t, 3>;

class Canvas {
public:

	explicit Canvas(uint16_t width, uint16_t height);
	~Canvas() {
		Flush();
	}

	void SetColorAt(const Color& color, uint16_t i, uint16_t j);
	Color GetColorAt(uint16_t i, uint16_t j) const;
	void Flush(const std::string& path = "");

private:

	const uint16_t width_;
	const uint16_t height_;
	std::vector<Color> buffer_;
};

#endif //CANVAS_H
