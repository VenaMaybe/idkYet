#pragma once
#include <string>

class Object {
public:
	// Constructor to enforce objType initialization
	explicit Object(const std::string& type) : objType(type) {} // explicit prevents unintended type conversions
	virtual ~Object() = default;

	virtual void render() const = 0;
	virtual void update() = 0;

	std::string getType();

	// Mark for removal using "Collect-Then-Erase" approach
	void markForRemoval() { removeFlag = true; }
	const bool isMarkedForRemoval() const { return removeFlag; }

protected: // All derived classes should access this
	std::string objType;
	bool removeFlag = false;
};