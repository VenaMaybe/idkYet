#define RLGL_STANDALONE
#include "raylib.h"
#include "rlgl.h"
#include "main_render.h"
#include "random.h"

void beginRaylibEnv(std::function<void()> doPerFrame, int SCREEN_WIDTH,	int SCREEN_HEIGHT) {
	// Don't want INFO logs
	SetTraceLogLevel(LOG_WARNING);

	// Initialize the window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inital Window");
	SetTargetFPS(60);
	
	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Start drawing
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(10, 10); // Draw FPS 

		// What happens every frame
		if (doPerFrame) {
			doPerFrame();
		}

		// Start a batch for rendering quads
		rlBegin(RL_QUADS);


		// Define a 2x2 rectangle at the position (pos->x, pos->y)
		float x = 100.f;
		float y = 100.f;
		float width = 20.0f;
		float height = 20.0f;

		// Add quad vertices (Clockwise order)
		rlColor4ub(255, 1, 255, 255); // Set color (RAYWHITE equivalent)
		rlVertex2f(x, y);                   // Top-left
		rlVertex2f(x + width, y);           // Top-right
		rlVertex2f(x + width, y + height);  // Bottom-right
		rlVertex2f(x, y + height);          // Bottom-left
		

		// End the batch
		rlEnd();

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