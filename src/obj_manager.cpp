#include <vector>
#include <algorithm> // for remove_if
#include "obj_manager.h"

std::string Object::getType() {
	return objType;
}

// Constructor
ObjMan::ObjMan() {}

// Render chain
void ObjMan::render() const {
	// Call objects render function
	for (const auto& object : objects)
		object->render();
}

void ObjMan::update() {
	// Call objects update function
	for (const auto& object : objects)
		object->update();
}

void ObjMan::addObject(std::unique_ptr<Object> obj) {
	objects.push_back(std::move(obj)); // Move ownership to the vector
}

void ObjMan::removeObjectViaPtr(Object* objToRemove) {
	// Moves elements to where predicate(true) to end of vector
	// 		w/ iterator to the first element to be erased
	auto it = std::remove_if( // Will remove all objects with that pointer
		objects.begin(),
		objects.end(),
		// Lambda to find the predicate
		[objToRemove](const std::unique_ptr<Object>& obj) { // gets access to [objToRemove]
			return obj.get() == objToRemove; // compare raw ptrs
		}
	);

	// Erase the elements form it to the end
	objects.erase(it, objects.end());
}