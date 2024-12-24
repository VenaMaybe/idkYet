// obj_manager.h
#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "object.h"

class ObjMan {
public:
	ObjMan();

	void handleInput(); // 1. Handle all input
	void update(float dt); // 2. Updates all objects
	void render() const; // 3. Renders all objects

	void addObject(std::unique_ptr<Object> obj);


/* 	template<typename T>
	T* addObject(std::unique_ptr<Object> obj) {
		
	} */

	// Get an object by name
	Object* getObjectByName(const std::string& name);

	// Get an object by name and safely downcast it to its type
	template<typename T>
	T* getObjectByNameAs(const std::string& name) {
		Object* obj = getObjectByName(name);
		// Return a safe downcast, nullptr if object pointed to isn't of type T
		return obj ? dynamic_cast<T*>(obj) : nullptr; // dynamic_cast allows for safe downcasting at runtime 
	}


	// void removeObjectViaPtr(Object* objToRemove);

private:
	// Holds a list of every object in the scene
	std::vector<std::unique_ptr<Object>> objects; 
	// Map names -> objects
	std::unordered_map<std::string, Object*> nameToObject;
};
