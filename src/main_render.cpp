#define RLGL_STANDALONE
#include "raylib.h"
#include "rlgl.h"
#include "main_render.h"
#include "random.h"

void beginRaylibEnv(std::function<void()> doPerFrame, int screen_width,	int screen_height) {
	// Don't want INFO logs
	SetTraceLogLevel(LOG_WARNING);

	// Initialize the window
	InitWindow(screen_width, screen_height, "Inital Window");
	// SetTargetFPS(60);
	
	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Start drawing
		BeginDrawing();
		ClearBackground(BLACK);

		// What happens every frame
		if (doPerFrame) {
			doPerFrame();
		}

		
		DrawFPS(10, 10); // Draw FPS 
		// End drawing
		EndDrawing();
	}

	// Close window and OpenGL context
	CloseWindow();
}

/* Utility functions */
void DrawOutlinedText(const char* text, int posX, int posY, int fontSize, int thickness, Color textColor, Color outlineColor) {
	// Draw the outline
	for (int dx = -thickness; dx <= thickness; dx++) {
		for (int dy = -thickness; dy <= thickness; dy++) {
			// Skip the center (main text position)
			if (dx == 0 && dy == 0) continue;

			DrawText(text, posX + dx, posY + dy, fontSize, outlineColor);
		}
	}
	// Draw the main text
	DrawText(text, posX, posY, fontSize, textColor);
}