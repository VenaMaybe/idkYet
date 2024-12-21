#include "edge.h"

// Constructor
Edge::Edge(const Vertex* from, const Vertex* to, float weight)
	: from(from), to(to), weight(weight) {}

// Used to render the vert
void Edge::render() const {
	if (!from || !to) return; // Make sure pointers are valid

	DrawLineEx(from->getPos(), to->getPos(), thickness, currentColor);
	DrawOutlinedText(TextFormat("%.f",weight), getCenterVertex().x, getCenterVertex().y, 20, 2, currentColor, BLACK);
}

void Edge::update() {}

void Edge::setWeight(float weight) {
	this->weight = weight;
}
void Edge::setColor(Color color) {
	this->currentColor = color;
}
void Edge::setThickness(float thickness) {
	this->thickness = thickness;
}
void Edge::setOutlined(bool outlined) {
	this->outlined = outlined;
}

Vector2 Edge::getCenterVertex() const {
	return  Vector2{static_cast<float>((from->getX()+to->getX())/2),
					static_cast<float>((from->getY()+to->getY())/2)};
}
const bool& Edge::getOutlined() const {
	return outlined;
}
const Vertex* Edge::getFrom() const {
	return from;
}
const Vertex* Edge::getTo() const {
	return to;
}