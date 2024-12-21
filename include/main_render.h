#pragma once
#include <functional>
#include "raylib.h"
#include "obj_manager.h"

// Raylib preamble
void beginRaylibEnv(
	std::function<void()> doPerFrame = nullptr,
	int SCREEN_WIDTH = 800,
	int SCREEN_HEIGHT = 450
);

// Drawing outlined text utility function
void DrawOutlinedText(const char* text, int posX, int posY, int fontSize, int thickness, Color textColor, Color outlineColor);