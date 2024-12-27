#pragma once
#include <functional>
#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

// Raylib preamble
void beginRaylibEnv(
	std::function<void()> doPerFrame = nullptr,
	int screen_width = SCREEN_WIDTH,
	int screen_height = SCREEN_HEIGHT
);

// Drawing outlined text utility function
void DrawOutlinedText(const char* text, int posX, int posY, int fontSize, int thickness, Color textColor, Color outlineColor);