// obj_manager.h
#pragma once
#include <memory>
#include <vector>
#include "object.h"

class ObjMan {
public:
	ObjMan();
	void render() const;
	void update();

	void addObject(std::unique_ptr<Object> obj);
	// void removeObjectViaPtr(Object* objToRemove);

private:
	// Holds a list of every object in the scene
	std::vector<std::unique_ptr<Object>> objects;
};
