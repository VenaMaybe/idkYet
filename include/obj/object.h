// object.h
#pragma once
#include <string>

class Object {
public:
	// Constructor to enforce objType initialization
	explicit Object(const std::string& type) 
		: objName(type), removeFlag(false) {} // explicit prevents unintended type conversions
	virtual ~Object() = default;

	// You better implement these later or else
	virtual void update(float dt) = 0;
	virtual void render() const = 0;

	// Getter
	inline std::string getName() const { return objName; }

	// Mark for removal using "Collect-Then-Erase" approach
	void markForRemoval() { removeFlag = true; }
	const bool isMarkedForRemoval() const { return removeFlag; }

protected: // All derived classes should access this
	std::string objName;
	bool removeFlag;
};