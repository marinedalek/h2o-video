#ifndef H2O_VIDEO_H_MARINEDALEK
#define H2O_VIDEO_H_MARINEDALEK
#include <raylib.h> 
#include <array>
#include <cstdint>
#include <iostream> 

namespace h2o {
struct Color_rgb {
	uint8_t	r;
	uint8_t g;
	uint8_t b;
};

using Palette = std::array<Color_rgb, 256>;


}
#endif