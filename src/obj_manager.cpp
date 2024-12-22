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
	
	// Collect and remove after update
	auto removeIt = std::remove_if(
		objects.begin(),
		objects.end(),
		// Lambda to find the predicate, check removal flag
		[](const std::unique_ptr<Object>& obj) {
			return obj->isMarkedForRemoval();
		}
	);

	// Erase the elements form removeIt to the end
	objects.erase(removeIt, objects.end());
}

void ObjMan::addObject(std::unique_ptr<Object> obj) {
	objects.push_back(std::move(obj)); // Move ownership to the vector
}

// Depricated, remove via pointer now remove via flag and sweep
/* void ObjMan::removeObjectViaPtr(Object* objToRemove) {
	if (!objToRemove) throw std::runtime_error("Tried to remove dangling pointer");

	// Moves elements to where predicate(true) to end of vector
	// 		w/ iterator to the first element to be erased
	auto removeIt = std::remove_if( // Will remove all objects with that pointer
		objects.begin(),
		objects.end(),
		// Lambda to find the predicate
		[objToRemove](const std::unique_ptr<Object>& obj) { // gets access to [objToRemove]
			return obj.get() == objToRemove; // compare raw ptrs
		}
	);

	// Erase the elements form removeIt to the end
	objects.erase(removeIt, objects.end());
} */