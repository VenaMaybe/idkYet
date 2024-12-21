#ifndef VERTEX_H
#define VERTEX_H

#include "raylib.h"
#include <functional>

// A vertex of the graph
class Vertex {
public:
	// Constructors
	Vertex() = default;
	Vertex(int x, int y);

	/*	Callback, stores a function that can be invoked when needed
		The idea is to treat a function as data that can be passed around and called later
		This function is of type void with input const Vertex*  */

	// This sets the callback from the outside
	void setOnClickCallback(std::function<void(Vertex*)> callback);
	// When we think a click has occurred on this vertex, we call the callback
	void handleClickEvent();

	void render() const; // Called every frame
	void update(); // Called every frame

	// Getters and Setters
	Vector2 getPos() const;
	int getX() const;
	int getY() const;
	void setRad(int radius);
	void setPos(int x, int y);
	void setColor(Color color);

	// Equality operator for Vertex
	bool operator==(const Vertex& other) const;
private:
	// Rendering
	Vector2 pos = {0, 0};
	int radius = 10;

	std::function<void(Vertex*)> onClickCallback; // Stores the callback

	// UTIL: Is the mouse within a certain distance? 
	bool isHovered(const Vector2& mousePos) const;
	void updateDragging(const Vector2& mousePos);
	void updateStartEnd(const Vector2& mousePos);

	// Current State
	Color currentColor = RAYWHITE;
	bool isDragging;

			// prob delete later
			bool isStart = false;
			bool isEnd = false;

	// Grant access to the hash specialization
	friend struct std::hash<Vertex>;
};

// From chatgpt
// Hash specialization for Vertex (needed for std::unordered_map)
namespace std {
	template <>
	struct hash<Vertex> {
		std::size_t operator()(const Vertex& v) const {
			// Combine the hashes of `x`, `y`, and `radius`
			std::size_t h1 = std::hash<int>()(v.pos.x);
			std::size_t h2 = std::hash<int>()(v.pos.y);
			std::size_t h3 = std::hash<int>()(v.radius);
			return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine with bitwise shifts and XOR
		}
	};
}

#endif // VERTEX_H