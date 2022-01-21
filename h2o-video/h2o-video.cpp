// h2o-video.cpp

#include "h2o-video.h"

int main()
{
	int constexpr screen_width{ 800 };
	int constexpr screen_height{ 600 };

	InitWindow(screen_width, screen_height, "h2o-video");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		EndDrawing();
	}

	return 0;
}
