#include "h2o-video.h"
#include <algorithm>
#include <array>
#include <format>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
	switch (argc) {
	case 1:
		std::cerr << "No filename provided. Exiting.\n";
		return 0;
	case 2:
		break;
	default:
		std::cerr << "Too many arguments. Exiting.\n";
		return 0;
	}

	auto h2o_file = std::ifstream(argv[1], std::ios::binary);
	if (!h2o_file.is_open()) {
		std::cerr << "Failed to open " << argv[1] << "\n";
		return 0;
	}
	std::array<char, 4> magic_string;
	h2o_file.read(magic_string.data(), 4);
	if (magic_string.at(0) != 0x48 ||	// H
		magic_string.at(1) != 0x32 ||	// 2
		magic_string.at(2) != 0x4F ||	// O
		magic_string.at(3) != 0x01) {
		std::cerr << "Not a valid H2O file. Exiting.\n";
		return 0;
	}
	std::cout << "H2O header found.\n";
	h2o_file.seekg(0x0001907e, std::ios::beg);
	std::cout << "Seek complete\n";
	h2o::Palette pal;
	h2o_file.read(reinterpret_cast<char*>(pal.data()), 3 * 256);
	std::cout << "Palette read from file\n";
	std::transform(pal.begin(), pal.end(), pal.begin(),
		[](h2o::Color_rgb& color)
		{ return h2o::Color_rgb{ uint8_t(color.r * 4),
								 uint8_t(color.g * 4),
								 uint8_t(color.b * 4) }; 
		});
	std::cout << std::format("Color 0 = ({:2x}, {:2x}, {:2x})\n",
		pal.at(0).r, pal.at(0).g, pal.at(0).b);

	int constexpr screen_width{ 800 };
	int constexpr screen_height{ 600 };

	InitWindow(screen_width, screen_height, "h2o-video");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		for (int i{0}; i < 256; ++i) {
			int x{ (i % 16) * 30 };
			int y{ (i / 16) * 30 };
			Color color{
				uint8_t{pal.at(i).r},
				uint8_t{pal.at(i).g},
				uint8_t{pal.at(i).b},
				255
			};
			DrawRectangle(x, y, 30, 30, color);
			
		}
		/*
		h2o_file.seekg(177600*0, std::ios::beg);
		for (int i{ 0 }; i < 177600; ++i) {
			int x{ (i % 296) };
			int y{ (i / 296) };
			uint8_t index{ uint8_t(h2o_file.get()) };
			Color color{
				uint8_t{pal.at(index).r},
				uint8_t{pal.at(index).g},
				uint8_t{pal.at(index).b},
				uint8_t{255}
			};
			DrawPixel(x, y, color);
		}
		*/

		EndDrawing();
	}

	return 0;
}