#pragma once
#include <string>

class Object {
public:
	// Constructor to enforce objType initialization
	explicit Object(const std::string& type) : objType(type) {} // explicit prevents unintended type conversions

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual ~Object() = default;
	std::string getType();

protected: // All derived classes should access this
	std::string objType;
};