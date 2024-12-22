#include <iostream>
#include "main_render.h"
#include "random.h"
#include "obj/obj_manager.h"

#include "ecs/registry.h"

int main() {
	ObjMan manager;

	std::cout << "Hello World" << std::endl;

	beginRaylibEnv([&manager](){
		manager.render();
		manager.update();
	});

	Registry registry;













	// Meows back to the computer
	return 0;
}